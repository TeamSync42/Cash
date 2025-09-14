# ADR-001: Shell Hash Table Architecture

-----

## 1. Context

The shell frequently needs to locate the executables corresponding to commands typed by the user. A sequential search
through the directories listed in the `$PATH` environment variable on each invocation is inefficient and hurts the
terminal’s responsiveness.

To mitigate this latency, the shell implements an internal cache in the form of a hash table. This table stores the
location of commands that have already been found, enabling near-instant access on further calls. This document
defines the architecture of this hash table, aiming for maximum performance and efficient memory management.

-----

## 2. Functional Requirements

### 2.1. General Behavior

* First invocation (command not present in the table):

    1. Traverse the directories in `$PATH` in order.
    2. If the executable is found, its absolute path is added to the table with a usage counter initialized to `1`.
    3. If the executable is not found, a “command not found” error is returned.

* Subsequent invocations:

    1. If the command is present in the table, its stored path is used directly for execution, and its usage counter is
       incremented.
    2. Otherwise, the behavior is the same as a first invocation.

### 2.2. Interface (hash built-in)

* `hash -r`: Completely clears the hash table.
* `hash -d <cmd>`: Removes only the specified `<cmd>` entry from the table.
* `hash -p <path> <cmd>`: Forcefully associates (or replaces) the command `<cmd>` with the path `<path>`. The usage
  counter is reset.
* `hash -t <cmd>`: Displays the cached absolute path for `<cmd>`. The return code is non-zero if the command is not in
  the cache.
* `hash` (without options): Displays the contents of the table, including usage counters.

### 2.3. Collision Handling and Uniqueness

* Command names are the unique keys of the table.
* Using `hash -p` on an existing command replaces the previous entry.
* Commands are distinguished by their name, not by their path.

-----

## 3. Architectural Model (C4 - Container Level)

* Person (Actor): The user typing commands in their terminal.
* System: Shell
    * Container: Command Executor — The core of the shell that interprets the command line.
    * Container: Hash Table Manager — The component responsible for managing the hash table. It exposes an internal API
      to the Command Executor and a user interface via the `hash` built-in.
    * Container: Filesystem Access Layer — Abstraction to interact with the filesystem, notably to traverse `$PATH`.

-----

## 4. Architecture Decision

To achieve maximum performance, the hash table implementation will use open addressing with linear probing.

### 4.1. Rationale

The bottleneck in high-performance data structures is often the main memory access. Linear probing maximizes CPU cache
locality. When memory access occurs at index `i`, the CPU loads not only that element but also its neighbors into its
fast caches (L1/L2). In the event of a collision, linear probing tests index `i+1`, which is very likely to already be
present in the cache.

This approach avoids the random memory accesses (pointer chasing) inherent in linked lists, which drastically reduces
latency and allows amortized O(1) complexity under optimal conditions.

### 4.2. Data Structure

The table will be a single contiguous array in memory.

```c++
// C
/**
 * @brief Represents a cached command entry in the hash table.
 */
typedef struct {
    char    *command_name;  // Key. If NULL, slot is empty. If TOMBSTONE, slot was deleted.
    char    *absolute_path; // Value.
    size_t  use_count;      // Usage counter.
}   t_hash_entry;

/**
 * @brief The main hash table structure.
 */
typedef struct {
    t_hash_entry    *table;     // Array of entries.
    size_t          table_size; // Total capacity of the array.
    size_t          item_count; // Number of occupied slots (excluding tombstones).
}   t_hash_table;
```

### 4.3. Handling Deleted Entries (“Tombstones”)

Direct deletion (setting `command_name` to `NULL`) would break probing chains. A sentinel value (“tombstone”) is used to
mark a slot as deleted while preserving probe continuity.

```c++
// C
# define TOMBSTONE ((char *) -1)
```

A slot `table[i]` can therefore have three states:

1. Empty: `table[i].command_name == NULL`
2. Occupied: `table[i].command_name` is a valid pointer.
3. Deleted: `table[i].command_name == TOMBSTONE`

### 4.4. Hash Function

A fast hash function with good distribution for strings is required. The djb2 algorithm is an excellent candidate due to
its simplicity and efficiency.

```c++
// C
/**
 * @brief Computes the hash of a string using the djb2 algorithm.
 * @param str The string to hash.
 * @return The calculated hash value.
 */
unsigned long hash_djb2(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}
```

### 4.5. Load Factor Management and Resizing

The performance of linear probing degrades rapidly as the table fills. It is imperative to keep a low load factor (
`lambda = item_count / table_size`).

* Resizing threshold: A rehash will be triggered as soon as the load factor exceeds 0.6 (60%).
* Resizing process:
    1. Allocate a new table of double the size.
    2. Traverse the old table.
    3. For each valid entry (non-`NULL` and non-`TOMBSTONE`), reinsert it into the new table by recalculating its index
       with the new size.
    4. Free the old table.

-----

## 5. Consequences of the Decision

### 5.1. Advantages

* Maximum Performance: Exceptional lookup speed thanks to cache locality.
* Optimal Memory Management: Low memory overhead (no chaining pointers). Allocations are grouped, reducing
  fragmentation.

### 5.2. Drawbacks

* Sensitivity to Load Factor: Performance depends on an aggressive and well-implemented resizing strategy.
* Deletion Complexity: Tombstone logic must be handled rigorously during lookups and insertions.
* Resizing Cost: The rehash operation is expensive, but its frequency is controlled and its cost amortized over the
  shell’s lifetime.