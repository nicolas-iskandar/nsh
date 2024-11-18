#include <stdio.h>
#include <stdlib.h>
#include "nsh.h"

int main(int argc, char **argv)
{
  printf("\033[H\033[J");

  nsh_loop();

  return 0;
}

void nsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do
  {
    printf("\e[1;37m$ ");
    line = nsh_read_line();
    args = nsh_split_line(line);
    status = nsh_execute(args);

    free(line);
    free(args);
  } while (status);
}
