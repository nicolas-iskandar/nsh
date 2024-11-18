#ifndef NSH_H
#define NSH_H

#define DEFAULT_BUF_SIZE 1024

void nsh_loop(void);
char *nsh_read_line(void);
char **nsh_split_line(char *line);
int nsh_execute(char **args);
int nsh_cd(char **args);
int nsh_help(char **args);
int nsh_pwd(char **args);
int nsh_echo(char **args);
int nsh_exit(char **args);
int nsh_launch(char **args);
int nsh_num_builtins(void);

extern char *builtin_str[];
extern char *builtin_str_descp[];
extern int (*builtin_func[])(char **);

#endif