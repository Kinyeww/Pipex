#ifndef PIPEX_H
# define PIPEX_H

//function name below
// typedef struct 

char	**check_arg(char *av);
char	**ft_split(const char *s, char c);
void	exepipe(char **cmd1, char **cmd2, char **envp, char **av);

#endif