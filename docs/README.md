<div align="center">

# MiniShell

![Norminette](https://img.shields.io/badge/Norm-passing-brightgreen?style=flat-square) ![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white) ![Makefile](https://img.shields.io/badge/Makefile-427819?style=flat-square) ![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black) ![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square)

*A fully functional shell implementation with advanced features.*

**Made by** [rmarin-j](https://github.com/rmarin-j) & [fmesa-or](https://github.com/fmesa-or)

</div>

---

## About the Project

MiniShell is a comprehensive shell implementation written in C that replicates core bash functionality. This project demonstrates advanced understanding of process management, signal handling, file descriptors, and command parsing. It serves as a practical learning experience in system programming and Unix principles at 42 School.

## Requirements

- Compiler: `gcc` or `clang`
- Flags: `-Wall -Wextra -Werror -g`
- OS: Linux
- Standard: C99 or later
- Libraries: `readline` (for input handling)
- Make: GNU Make

### System Dependencies

```bash
# Ubuntu/Debian
sudo apt-get install libreadline-dev

# Fedora
sudo dnf install readline-devel
```

## Installation and Usage

### Building

```bash
# Clone the repository
git clone https://github.com/usuario/MiniShell.git
cd MiniShell

# Compile the shell
make

# Clean build artifacts
make clean

# Remove all generated files
make fclean

# Rebuild everything
make re
```

### Running MiniShell

```bash
# Start the shell
./minishell

# Your shell prompt will appear:
minishell$ 
```

### Basic Usage

```bash
# List files
minishell$ ls -la

# Navigate directories
minishell$ cd /tmp

# Print environment variables
minishell$ env

# Use pipes
minishell$ ls -la | grep ".c"

# Redirections
minishell$ echo "Hello" > file.txt
minishell$ cat file.txt
minishell$ echo "World" >> file.txt

# Heredoc
minishell$ cat << EOF
> This is a heredoc
> Multiple lines supported
> EOF
This is a heredoc
Multiple lines supported
```

## Implemented Features

### Built-in Commands

- **`echo`** - Display text (with `-n` flag support)
- **`cd`** - Change directory (with relative and absolute paths)
- **`pwd`** - Print working directory
- **`export`** - Set environment variables
- **`unset`** - Remove environment variables
- **`env`** - Display environment variables
- **`exit`** - Exit the shell with optional status code

### Input/Output Redirection

- **`>`** - Output redirection (overwrite)
- **`>>`** - Output redirection (append)
- **`<`** - Input redirection
- **`<<`** - Heredoc (here-document)

### Piping

- **`|`** - Pipe operator for chaining commands
- Full support for multiple pipes in a single command

### Variable Expansion

- **`$VARIABLE`** - Variable expansion
- **`$?`** - Last command exit status
- Quoted string expansion with proper escaping

### Signal Handling

- **`Ctrl+C`** - Interrupt current process
- **`Ctrl+\\`** - Quit signal
- **`Ctrl+D`** - EOF (exit shell)
- Proper signal inheritance for child processes

### Advanced Features

- Command history (via readline library)
- Multiple redirections per command
- Error handling and exit status codes
- Proper memory management (no leaks)
- Environment variable inheritance

## File Structure

```
.
├── Makefile                      # Compilation rules
├── include/
│   └── minishell.h              # Main header file
├── docs/
│   └── README.md                # This file
└── src/
    ├── minishell.c              # Main entry point
    ├── execute/                 # Command execution
    │   ├── builtins/            # Built-in commands
    │   ├── exe_redir/           # Redirection handling
    │   ├── execution/           # Process execution
    │   └── utils_exe/           # Execution utilities
    ├── parse/                   # Parsing logic
    │   ├── expand/              # Variable expansion
    │   ├── get_argv/            # Argument processing
    │   └── parse.c              # Main parser
    ├── prompt/                  # Prompt handling
    ├── signals/                 # Signal management
    ├── mem/                     # Memory management
    └── utils/                   # Utility functions
```

## Compilation Notes

- The binary is created as: `minishell`
- All code follows the 42 School Norm standards
- Comprehensive memory management to prevent leaks
- Proper file descriptor handling and cleanup
- Signal handlers prevent zombie processes

## Testing Expected Output

### Basic Command
```bash
minishell$ echo "Hello World"
Hello World
```

### Pipes
```bash
minishell$ echo -e "apple\nbanana\napple" | grep apple
apple
apple
```

### Redirection
```bash
minishell$ echo "test" > output.txt
minishell$ cat output.txt
test
```

### Exit Status
```bash
minishell$ ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
minishell$ echo $?
2
```

### Heredoc
```bash
minishell$ cat << EOF
> Enter text here
> Type EOF to end
> EOF
Enter text here
Type EOF to end
```

## Debugging and Valgrind

Check for memory leaks:

```bash
# Compile the project
make

# Run with valgrind
valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Example checking a simple command
echo "exit" | valgrind --leak-check=full ./minishell
```

## Known Limitations

- Some advanced bash features not implemented
- Limited to single-line commands
- No job control (background processes with `&`)
- Limited glob pattern matching
- No command substitution syntax

## Performance Considerations

- Optimized for correctness over performance
- Uses efficient memory allocation strategies
- Minimizes system calls where possible
- Proper use of `fork()` and `exec()` family functions

## Troubleshooting

### Compilation Issues

```bash
# If readline is not found
make clean
make

# For macOS with Homebrew readline
export LDFLAGS="-L/usr/local/opt/readline/lib"
export CPPFLAGS="-I/usr/local/opt/readline/include"
make
```

### Runtime Issues

- If history is not working, ensure readline is properly installed
- Use `Ctrl+D` to exit if the shell becomes unresponsive
- Check permissions for files being accessed

## Project Goals Achieved

✅ Full command parsing and execution  
✅ Proper signal handling  
✅ Complete redirection system  
✅ Variable expansion  
✅ Built-in command implementation  
✅ Memory leak-free execution  
✅ Multiple pipe support  
✅ Environment variable management  

---

<div align="center">
Made with ☕ at <a href="https://42malaga.com">42 Málaga</a>
</div>
