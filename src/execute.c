#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "nsh.h"

int nsh_execute(char **args)
{
  int i;

  if (args[0] == NULL)
  {
    return 1;
  }

  for (i = 0; i < nsh_num_builtins(); i++)
  {
    if (strcmp(args[0], builtin_str[i]) == 0)
    {
      return (*builtin_func[i])(args);
    }
  }

  return nsh_launch(args);
}

int nsh_launch(char **args)
{
  pid_t pid;
  int status;

  // Here I'm forking (creating a copy of) the parent process and replacing the running program in it with the given command's program
  pid = fork();
  if (pid == 0)
  {
    if (execvp(args[0], args) == -1)
    {
      perror("\033[31mnsh");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    perror("\033[31mnsh");
  }
  else
  {
    do
    {
      // Wait for the child process to terminate and stores the exit status in the status variable.
      // WUNTRACED means that the function will also return if a child process has stopped
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}