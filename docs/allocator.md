# ADR-002: Hybrid Memory Allocator

-----

## 1. Context

The project needs a memory allocator that is memory- and CPU-efficient for the shell runtime. Typical workloads include
short-lived allocations during the execution step, occasional larger buffers (strings, bytecode), and the need to be
embeddable and usable in constrained environments (stack-only builds).

Goals:

- Very low allocation overhead for short-lived objects used during execution.
- Predictable behavior and low fragmentation for long-lived small objects.
- Tunability at compile-time to support stack-only (no-heap) builds and different slab/arena counts.

-----

## 2. Functional Requirements

### 2.1. General Behavior

1. Arena allocations:

  - Fast, contiguous bump allocator intended for short-lived allocations with the same lifetime (execution-pass scoped).
  - Arena allocations are freed **only** by resetting/destroying the arena (no individual `free`).
  - Arenas attempt allocations on an on-stack region first (when compiled with stack-capable mode). If the stack region
    is exhausted, allocations fall back to heap-backed arena regions unless stack-only mode is explicitly selected at
    runtime/compile-time.
  - Arena count is tunable at compile time via the build flag `STACK_ARENAS`.

2. Slab allocations:

  - For frequently allocated small objects with variable lifetimes and for allocations that must be individually freed.
  - Size classes up to `MAX_SLAB_SIZE` (tunable at build time) with per-class freelists and slab metadata.
  - Requirement: `MAX_SLAB_SIZE` must never exceed `SLAB_CAPACITY - sizeof(t_slab_meta)`.
  - Slabs are allowed to live on the heap and be individually freed; `allocator_free(alloc)` returns the slot to the
    slab pool.

3. System fallback (heap)

  - For allocations larger than `MAX_SLAB_SIZE` or when slab/backing pools are exhausted, fall back to standard heap
    allocation.
  - If the binary is built in a stack-only (no-heap) configuration, the fallback to heap is disabled and such
    allocations fail with a clear error.

### 2.2. Configuration

- Compile-time constants define arena and slab counts (e.g. `STACK_ARENAS`, `STACK_SLABS`).
- `MAX_SLAB_SIZE` must not exceed `SLAB_CAPACITY - sizeof(t_slab_meta)`.
- `ARENA_CAPACITY` is internally page-size aligned and not user-tunable; counts are tunable instead.

### 2.3. Ownership Rules

- Arena allocations: same-lifetime group — freed only by `allocator_arena_free()`. If multiple arenas share an
  `arena_id`, they will be reset as a chain.
- Slab allocations: individually freeable via `allocator_free()`.
- Heap allocations: freed via `allocator_free()`.

### 2.4. Interface

- `allocator_init()`, `allocator_destroy()` - global allocator lifecycle.
- `allocator_arena_new()`, `allocator_arena_free()` - arena API.
- `allocator_alloc()`, `allocator_free()` - general API.

### 2.5. Constraints

- Page-size alignment required for arenas to maximize performance.
- Allocation metadata must allow reliable determination of allocation origin during free.
- Careful implementing of ID-reusal is required to avoid unexpected behavior.

-----

## 3. Architectural Model

- Person (Actor): Shell runtime requesting allocations.
- System: Allocator subsystem
  - Container: Arena Manager - provides transient allocations.
  - Container: Slab Manager - provides fixed-size alloc/free.
  - Container: Heap Fallback - handles oversized or unsupported allocations.

- Bump arenas provide minimal-cost allocation for the dominant short-lived allocation pattern during execution passes.
- Slab pools reclaim and reuse fixed-size objects efficiently and enable individual frees for persistent objects.
- Stack-first arenas + compile-time tunables support embedding the shell in constrained environments.
- Single-thread assumption simplifies implementation and reduces overhead.

-----

## 4. Architecture Decision

Adopt a hybrid allocator composed of bump arenas for transient allocations, slab pools for small persistent allocations,
and heap fallback for large allocations. Stack-only mode disables heap fallback.

### 4.1. Rationale

- Performance: Bump arenas enable nearly zero-cost allocations for transient data. Slabs minimize fragmentation and
  provide O(1) allocation/free for small persistent objects. Heap fallback is reserved for rare oversized cases.
- Flexibility: The allocator adapts to both embedded (stack-only) and full-host environments.

### 4.2. Data Structures

- `t_allocator`: The main allocator structure, should be stack-allocated for best performance.
- `t_arena`: Represents a contiguous memory block with a bump pointer and optional link to a chained arena.
- `t_slab`: Represents a fixed-size pool with metadata headers and slots allocated linearly.
- `t_allocation`: Returned handle that contains a pointer to the allocated memory (`data`) and metadata required for
  freeing without relying on hidden internals.

### 4.3. Allocation Flow
1. Request enters via `allocator_alloc()`.
2. If an `arena` pointer is provided, attempt `arena` allocation, move bump pointer and return `t_allocation` with
  type `ALLOC_ARENA`
3. If size <= `MAX_SLAB_SIZE`, attempt slab allocation. Return `t_allocation` with type `ALLOC_SLAB`
4. If size > `MAX_SLAB_SIZE`, use heap allocation unless stack-only mode is active.

-----

## 5. Consequences

### 5.1. Advantages

- Speed: Arenas provide extremely fast, linear allocations; slabs reduce overhead for small objects.
- Memory efficiency: Page-sized arenas minimize wasted space; slabs reuse freed slots efficiently.
- Embedded readiness: Stack-only mode allows running without heap usage.
- Predictable lifetimes: Arena reset semantics simplify memory discipline for transient allocations.
- Maintainability: Explicit `t_allocation` structures avoid hidden globals and make provenance visible.

### 5.2. Drawbacks

- API complexity: Returning `t_allocation` instead of raw `void *` adds indirection and requires callers to handle an
  extra type.
- Learning curve: Developers must understand arena vs slab semantics to avoid misuse
  (e.g., dangling arena pointers after reset)
- Overhead for tiny allocations: The `t_allocation` wrapper introduces a small amount of metadata overhead compared to
  direct pointers.
- Limited Flexibility: Arena allocations cannot be freed individually; misuse leads to logical errors.
