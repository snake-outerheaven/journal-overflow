#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void parse_input(char *line, char **args) {
  char *token;
  int i = 0;

  token = strtok(line, " \t\n\r");
  while (token != NULL && i < MAX_ARGS - 1) {
    args[i] = token;
    i++;
    token = strtok(NULL, " \t\n\r");
  }
  args[i] = NULL;
}

int main() {
  char line[MAX_LINE];
  char *args[MAX_ARGS];
  pid_t pid;
  int status;

  while (1) {

    printf("%% "); 
    fflush(stdout);

    if (fgets(line, sizeof(line), stdin) == NULL) {
      printf("\n");
      break; 
    }

    // 3. Parse input into arguments
    parse_input(line, args);

    // If user pressed enter without typing anything, skip
    if (args[0] == NULL) {
      continue;
    }

    // 4. Handle Shell Built-ins (Executed by parent, no fork)
    if (strcmp(args[0], "exit") == 0) {
      break;
    }

    // 5. External Commands (Requires Fork and Exec)
    pid = fork();

    if (pid < 0) {
      // Fork failed
      perror("Fork failed");
      exit(1);
    } 
    else if (pid == 0) {
      // --- CHILD PROCESS ---
      // execvp takes the filename and the array of arguments.
      // It automatically searches the directories in your $PATH variable.
      if (execvp(args[0], args) == -1) {
	perror("Command execution failed");
      }
      exit(1); // Exit child process if exec fails
    } 
    else {
      // --- PARENT PROCESS ---
      // Parent blocks and waits for the child process to finish running
      waitpid(pid, &status, 0);
    }
  }

  return 0;
}
