#include <stdio.h>    // For input/output functions (printf, fgets)
#include <stdlib.h>   // For general utilities (exit, NULL)
#include <unistd.h>   // For system calls (fork, execvp)
#include <sys/types.h> // For pid_t
#include <sys/wait.h> // For wait
#include <string.h>   // For string manipulation (strtok)

// Define the maximum size for the command line input
#define MAX_LINE 80 
// Define the maximum number of arguments a command can take
#define MAX_ARGS 10 

void parse_command(char *command, char **args) {
    // A simple implementation of parsing the command line input
    // It splits the string by spaces and stores tokens in the 'args' array.
    
    char *token;
    int i = 0;

    // Use strtok to get the first token (the command name)
    token = strtok(command, " \n");
    
    while (token != NULL && i < MAX_ARGS - 1) {
        // Store the token (argument) in the arguments array
        args[i] = token;
        i++;
        // Get the next token
        token = strtok(NULL, " \n");
    }
    
    // The execvp function requires the last element of the arguments array to be NULL.
    args[i] = NULL;
}

void execute_command(char **args) {
    // 1. Create a new process (Child process)
    pid_t pid = fork();

    if (pid < 0) {
        // Error handling for fork failure
        perror("fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) {
        // --- CHILD PROCESS CODE ---
        
        // 2. Execute the command
        // execvp replaces the current process image with a new one.
        // It searches for the executable file in the directories specified by the PATH environment variable.
        // args[0] is the command name (e.g., "ls")
        // args is the array of arguments (e.g., ["ls", "-l", NULL])
        if (execvp(args[0], args) == -1) {
            perror("execvp error");
            // If execvp fails, the child must exit immediately
            exit(EXIT_FAILURE);
        }
    } 
    else {
        // --- PARENT PROCESS CODE ---
        
        // 3. Wait for the child process to complete
        // The parent shell waits until the command finishes execution.
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid error");
        }
    }
}

int main() {
    char input_line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        // Display the shell prompt
        printf("simple_shell> ");
        fflush(stdout); // Ensure the prompt is immediately displayed
        
        // Read the command from the user
        if (fgets(input_line, MAX_LINE, stdin) == NULL) {
            // Handle EOF (Ctrl+D)
            printf("\nExiting shell...\n");
            break;
        }

        // Check for the "exit" command
        if (strncmp(input_line, "exit", 4) == 0) {
            printf("Exiting shell...\n");
            break;
        }

        // Parse the input string into command and arguments
        parse_command(input_line, args);

        // Check if any command was actually entered
        if (args[0] != NULL) {
            execute_command(args);
        }
    }

    return 0;
}
