#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "nsh.h"

char *nsh_read_line(void)
{
  char *line = NULL;
  size_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1)
  {
    if (feof(stdin))
    {
      exit(EXIT_SUCCESS);
    }
    else
    {
      perror("\033[31mnsh");
      exit(EXIT_FAILURE);
    }
  }

  return line;
}

#define NSH_TOKEN_BUFSIZE 64
#define NSH_TOKEN_DELIM " \t\r\n\a"

char **nsh_split_line(char *line)
{
  int bufsize = NSH_TOKEN_BUFSIZE;
  int position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token;

  if (!tokens)
  {
    fprintf(stderr, "\033[31mnsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, NSH_TOKEN_DELIM);
  while (token != NULL)
  {
    tokens[position] = token;
    position++;

    if (position > bufsize)
    {
      bufsize += NSH_TOKEN_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char *));

      if (!tokens)
      {
        fprintf(stderr, "\033[31mnsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, NSH_TOKEN_DELIM);
  }

  tokens[position] = NULL;
  return tokens;
}