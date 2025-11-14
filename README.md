# mini-shell-c

💻 Mini-Shell: A Custom Command Line Interpreter (C)
A fundamental Command Line Interpreter (CLI), or "Mini-Shell," developed in C. This project simulates core shell functionality, providing a robust platform to demonstrate mastery of low-level Operating System concepts and POSIX system programming.


✨ Key Features
 * Command Execution: Supports execution of standard system commands (e.g., ls, cat, echo, pwd) with arguments.
 * Process Isolation: Commands are executed within their own child processes, ensuring the main shell process remains stable.
 * Synchronous Execution: The parent shell intelligently waits for the child process to complete execution before prompting the user for the next command.
 * Built-in Exit: Recognizes and handles the exit command to gracefully terminate the shell.

   
⚙ Technical Deep Dive
This project strictly employs core C language features and POSIX system calls to manage processes and handle execution flow:
| C Concept | POSIX System Call | Purpose |
|---|---|---|
| Process Control | fork() | Creates a duplicate child process to safely run external commands. |
| Execution | execvp() | Replaces the child's program image with the desired executable (e.g., ls), searching the system's $PATH. |
| Concurrency Management | waitpid() | Ensures the shell (parent process) pauses execution until the command (child process) finishes, maintaining correct shell behavior. |
| String Handling | strtok() | Utilized for robust parsing of the raw input string, accurately separating the command from its arguments. |
| Memory Management | fgets(), Pointer Arithmetic | Handles input buffers and argument arrays efficiently, preventing common C memory leaks associated with command parsing. |

🚀 Building and Running
This program is designed to be compiled and run on Unix-like systems (Linux, macOS, or WSL on Windows) where POSIX headers are available.
Prerequisites
 * A C compiler (e.g., GCC - GNU Compiler Collection).
Compilation
 * Navigate to the project directory in your terminal.
 * Compile the source code:
   gcc simple_shell.c -o simple_shell

Execution
 * Run the compiled executable:
   ./simple_shell

 * When the prompt appears (simple_shell> ), enter your command:
   simple_shell> ls -l
simple_shell> echo Hello World
simple_shell> exit
