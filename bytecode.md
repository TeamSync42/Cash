# Cash VM Bytecode Reference

Each instruction starts with a 1-byte **opcode**.
Arguments follow immediately and are encoded in **little endian** unless noted.

---

## Instruction Set

| Opcode       | Value | Format                                  | Description |
|--------------|-------|-----------------------------------------|-------------|
| `OP_NULL`    | 0x00  | `[opcode]`                              | No-op / placeholder. |
| `OP_COMMAND` | 0x01  | `[opcode][argc:4]`                      | Start a new command, declaring number of arguments. |
| `OP_EXEC`    | 0x02  | `[opcode]`                              | Execute current command with collected args. |
| `OP_ARG`     | 0x03  | `[opcode][len:1][bytes:len]`            | Append argument string. |
| `OP_FILENAME`| 0x04  | `[opcode][len:1][bytes:len]`            | Provide filename (for redirections). |
| `OP_PIPE`    | 0x05  | `[opcode]`                              | Start a new command in a pipeline (`\|`). |
| `OP_BACKGROUND` | 0x06 | `[opcode]`                            | Run preceding pipeline in background (`&`). |
| `OP_REDIR_OUT` | 0x07 | `[opcode][fd:4]`                       | Redirect output of previous command to file. |
| `OP_REDIR_IN`  | 0x08 | `[opcode][fd:4]`                       | Redirect input of previous command from file. |
| `OP_JZ`      | 0x09  | `[opcode][offset:4]`                    | Jump if pipeline exit code is zero. |
| `OP_JNZ`     | 0x0A  | `[opcode][offset:4]`                    | Jump if pipeline exit code is not zero. |
| `OP_WAIT`    | 0x0B  | `[opcode]`                              | Wait for background jobs. Equivalent to shell `wait`. |
| `OP_COUNT`   | 0x0C  |                                         | Sentinel (number of opcodes); not normally emitted. |

---

## Encoding Notes

- **Strings**: encoded as `[len:1][bytes:len]`.  
- **Integers**: 4-byte little endian.  
- `OP_COMMAND` uses `argc` as an integer, followed by `argc` `OP_ARG` instructions.
- Redirections (`OP_REDIR_IN/OUT`) require a preceding `OP_FILENAME`.

---
