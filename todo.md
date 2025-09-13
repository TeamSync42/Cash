# POSIX-compliant shell TODO (IEEE 1003.1–2017 aligned)

- [ ] Compliance scope
    - [ ] Target: POSIX Shell Command Language (XCU sh) and Utilities
    - [ ] Document each deviation (if any) with rationale
    - [ ] Make “non-POSIX extras” gated behind an explicit option (default off)

- [ ] Grammar and parsing (command language)
    - [ ] Tokens and separators: '\n', ' ', '\t', '\r', '\v', '\f', comments starting with #
    - [ ] Reserved words: !, {, }, case, do, done, elif, else, esac, fi, for, if, in, then, until, while, time
    - [ ] Compound commands
        - [ ] ( list ) subshell
        - [ ] { list ; } grouping in the current shell
        - [ ] for name [in words] ; do list ; done
        - [ ] case word in pattern) list ;; … esac
        - [ ] if list ; then list [; elif list ; then list]… [; else list] ; fi
        - [ ] while list ; do list ; done
        - [ ] until list ; do list ; done
        - [ ] time pipeline
        - [ ] Lists and pipelines
        - [ ] list: command [;|&|\n] command …
        - [ ] pipeline: command [| command]…
        - [ ] pipeline with bang: ! pipeline (invert exit status)
    - [ ] Command forms
        - [ ] simple command: prefix (assignments, redirs) + words
        - [ ] function definition: name() compound-command [redir]
        - [ ] Command search order: aliases > special builtin > function > regular builtin > PATH utility

- [ ] Tokenization, quoting, and expansions (order matters)
    - [ ] Tokenization with quotes/backslash rules
    - [ ] Tilde expansion (only in assignment-value and unquoted words where permitted)
    - [ ] Parameter expansion: \$\{var\}, \$\{var:-word\}, \$\{var:=word\}, \$\{var:?word\},
        \$\{var:+word\}, \$\{#var\}, \$\{var%…\}, \$\{var%%…\}, \$\{var#…\}, \${var##…\}
    - [ ] Command substitution: $(command) and \`command\`
        - [ ] Properly handle nested $(…) and backticks with escaping
        - [ ] Newline trimming from output per POSIX
    - [ ] Arithmetic expansion: $(( expression )) (C-like, locale-independent, intmax_t)
    - [ ] Field splitting using IFS after expansions
    - [ ] Pathname expansion (globbing): *, ?, […] with locale collation; ‘set -f’ disables
    - [ ] Quote removal (final step)
    - [ ] Here-doc processing and expansion rules
        - [ ] << word (expand)
        - [ ] <<- word (expand, strip-leading tabs)
        - [ ] No expansion if the delimiter is quoted

- [ ] Redirections (exact POSIX set)
    - [ ] [n]>word, [n]>>word, [n]<word, [n]<>word
    - [ ] [n]>&word, [n]<&word (dup/close if the word is ‘-’)
    - [ ] Here-doc: [n]<<word, [n]<<-word
    - [ ] Redirection semantics for special builtins (apply before assignment effects)
    - [ ] Ensure file descriptor lifetime, CLOEXEC where appropriate

- [ ] Execution environment and semantics
    - [ ] PATH search, leading slashes, emptily fields semantics, ‘.’ handling per POSIX
    - [ ] Environment inheritance and assignments preceding utilities
    - [ ] Rehash policy: optional cache must invalidate when PATH changes
    - [ ] Exit status rules:
        - [ ] simple command: exit of the utility
        - [ ] pipeline: exit of last command (no pipe-fail by default)
        - [ ] lists: last command in the list
        - [ ] ! inverts 0/!0
    - [ ] Traps and signals: trap, EXIT behavior, reset on exec per POSIX
    - [ ] Reaping: wait semantics, background jobs
    - [ ] Locale: LC_ALL/LC_CTYPE/LC_COLLATE effects on globbing, sorting
    - [ ] umask inheritance and application to redirections

- [ ] Builtins (POSIX)
    - [ ] Special builtins (must behave exactly; affect shell state, error handling different)
        - [ ] : (no-op)
        - [ ] . pathname [args]
        - [ ] break [n]
        - [ ] continue [n]
        - [ ] eval args…
        - [ ] exec [redir …] [utility [args…]]
        - [ ] exit [n]
        - [ ] export [-p] name[=value] …
        - [ ] readonly [-p] name[=value] …
        - [ ] return [n] (functions only)
        - [ ] set [flags] [--] [positional…]
        - [ ] shift [n]
        - [ ] source pathname [args]
        - [ ] times
        - [ ] trap [action] [signals…]
        - [ ] unset [-fv] name…
    - [ ] Regular builtins (POSIX)
        - [ ] alias [-p] [name[=value]…]
        - [ ] bg [jobspec…] (if job control implemented)
        - [ ] cd [-L|-P] [dir]
            - [ ] Absolute, relative
            - [ ] CDPATH
            - [ ] ~ expansion to $HOME only where specified
            - [ ] 
                - switches to $OLDPWD and prints dir
        - [ ] command [-p] [-v|-V] name…
            - [ ] command -v for portable “type”
        - [ ] fc [-e editor] [first [last]] | -l [-nr] [first [last]] | -s [old=new] [first]
        - [ ] fg [jobspec] (if job control)
        - [ ] getopts optstring name [args]
        - [ ] jobs [-l|-p] [jobspec…] (if job control)
        - [ ] kill [-s signame| -signum] pid|jobspec …
        - [ ] read [-r] [-p prompt] [-u fd] [-t timeout] [-n n] name…
        - [ ] ulimit [options] [value]
        - [ ] umask [mode]
        - [ ] unalias [-a] name…
        - [ ] wait [jobspec|pid]…
    - [ ] Utilities that are POSIX but not required as builtins (provide via PATH; builtin optional)
        - [ ] printf (preferred over echo for portability)
        - [ ] echo (if provided, must follow POSIX: ‘echo -n’ is implementation-defined; avoid -e/-E)
        - [ ] pwd (external utility acceptable; builtin optional)
        - [ ] test and [ … ] (must be consistent)
        - [ ] env (external)

- [ ] Job control (optional but POSIX-specified)
    - [ ] Enable only if interactive and the system supports it
    - [ ] Background (&), fg, bg, jobs, %jobspec parsing
    - [ ] Terminal control (tcsetpgrp), process groups, stopped/running states
    - [ ] Disallow job control features in non-interactive mode per POSIX

- [ ] Functions and positional parameters
    - [ ] Function definition and scope: name(), no ‘function’ keyword (non-POSIX)
    - [ ] Locality of set -e/-u etc. across functions per POSIX
    - [ ] \$0, \$1…\$n, \$#, \$*, \$@, \$?, \$\$, \$!, \$-, \$_
    - [ ] set—to reset positional parameters; shift semantics

- [ ] Options and shell flags (set/unset)
    - [ ] -a allexport, -b notify, -e errexit, -f noglob, -h (hashcmds, if implemented), -n noexec, -u nounset, -v
      verbose, -x xtrace
    - [ ] -o POSIXLY_CORRECT effects (or POSIX mode toggle), and mapping from common -o names
    - [ ] Ensure special builtins error handling (non-interactive: errors are fatal)

- [ ] Pathname resolution and security
    - [ ] Avoid executing from the current directory unless the PATH includes “.”
    - [ ] Handle empty PATH entries as the current directory
    - [ ] Disallow setuid/setgid interpretation within shell builtins
    - [ ] Respect execve() errors and report per POSIX

- [ ] Error handling and diagnostics
    - [ ] Consistent diagnostic format: utility: message
    - [ ] set -e precise rules (don’t trigger after while/if conditions, in &&/|| lists per POSIX)
    - [ ] trap ERR is not POSIX; exclude
    - [ ] Non-zero status for redirection failures before running utility

- [ ] Interactive behavior (POSIX only)
    - [ ] PS1, PS2, PS4, and prompt expansion rules (minimal, POSIX)
    - [ ] Command history only as required by fc; line editing/bind/readline are non-POSIX (exclude)
    - [ ] Ignore SIGINT on the interactive shell; foreground jobs receive it

- [ ] Exclusions (explicitly non-POSIX; keep out of default build)
    - [ ] [[ … ]], (( … )), here-strings (<<<), process substitution <( ), >( )
    - [ ] Brace expansion {a,b}, \$'…', \$"...", =~ operator, coprocess, disown, bind, caller, shopt
    - [ ] function keyword, arrays, associative arrays, mapfile/readarray, select
    - [ ] pipe-fail, globstar, extglob (non-POSIX variants)
    - [ ] jobspec %?string fuzzy forms beyond POSIX

- [ ] Testing and conformance
    - [ ] Create a conformance test suite:
        - [ ] Grammar/compound command tests
        - [ ] Expansion order tests (IFS, globbing, quoting)
        - [ ] Redirection matrix (including fd duplication/close)
        - [ ] Builtins behavior with edge cases
        - [ ] set -e, -u, -f, -x behavior
        - [ ] trap and signal tests
        - [ ] Subshell vs grouping environment changes
        - [ ] PATH search ordering and ‘command -v’ correctness
        - [ ] Here-doc expansion and tab-stripping
    - [ ] Cross-run against: dash, busybox sh, ksh93 (for reference), and posix mode of bash
    - [ ] Integrate a POSIX test suite (OpenPOSIX, posixtestsuite) where applicable
    - [ ] Fuzzing: tokenizer and parser

- [ ] Performance and limits
    - [ ] Large here-docs and pipelines
    - [ ] Many positional parameters and deep recursion in functions
    - [ ] File descriptor leak tests across exec

- [ ] Documentation
    - [ ] Manpage aligned with POSIX sections
    - [ ] Document undefined/unspecified behaviors you choose
    - [ ] Quick portability notes (use printf instead of echo, prefer command -v, etc.)

- [ ] Edge cases
    - [ ] :(){ :|:& };: (fork bomb) — ensure ulimit -u / RLIMIT_NPROC and set -m/job control interactions don’t crash
      shell
    - [ ] set -e with pipelines, command substitutions, and in if/while conditions
    - [ ] IFS empty vs unset differences
    - [ ] cd with CDPATH causing output; scripts depending on quiet cd
    - [ ] trap with signals delivered during builtin redirections
    - [ ] Handling of nonexistent executables vs permission denied (126 vs 127)

- [ ] Implementation hints (non-normative checklist)
    - [ ] Enforce expansion order via explicit phases
    - [ ] Separate parser AST for lists/pipelines/compound commands
    - [ ] Distinguish special builtins to apply redirections and error semantics early
    - [ ] Maintain job table only when interactive
    - [ ] Locale-sensitive paths for globbing; LC_ALL=C tests for deterministic behavior
