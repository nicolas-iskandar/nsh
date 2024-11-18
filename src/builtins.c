#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "nsh.h"

char *builtin_str[] = {"cd",
                       "help",
                       "pwd",
                       "echo",
                       "exit"};

char *builtin_str_desc[] = {"Change Directory",
                            "Overview of nsh",
                            "Print Working Directory",
                            "Print a specific message",
                            "Exit the program"};

int (*builtin_func[])(char **) = {
    &nsh_cd,
    &nsh_help,
    &nsh_pwd,
    &nsh_echo,
    &nsh_exit};

int nsh_cd(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "\033[31mnsh: expected argument to \"cd\"\n");
  }
  else if (chdir(args[1]) != 0)
  {
    perror("\033[31mnsh");
  }

  return 1;
}

int nsh_help(char **args)
{
  int i;
  printf("Usage: nsh <command> [<args>]\n");

  for (i = 0; i < nsh_num_builtins(); i++)
  {
    printf("  %-10s %s\n", builtin_str[i], builtin_str_desc[i]);
  }

  return 1;
}

int nsh_pwd(char **args)
{
  char cwd[DEFAULT_BUF_SIZE];
  if (getcwd(cwd, sizeof(cwd)) != NULL)
  {
    printf("%s\n", cwd);
  }
  else
  {
    perror("\033[31mnsh");
  }
  return 1;
}

int nsh_echo(char **args)
{
  for (int i = 1; args[i] != NULL; i++)
  {
    char *arg = args[i];

    while (*arg != '\0')
    {
      if (*arg != '"' && *arg != '\'')
      {
        putchar(*arg);
      }
      arg++;
    }

    if (args[i + 1] != NULL)
    {
      putchar(' ');
    }
  }
  printf("\n");
  return 1;
}

int nsh_exit(char **args)
{
  return 0;
}

int nsh_num_builtins()
{
  return sizeof(builtin_str) / sizeof(char *);
}