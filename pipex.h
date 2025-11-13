#ifndef PIPEX_H
# define PIPEX_H

#include <stddef.h>
//function name below
// typedef struct 

char	**check_arg(char *av);
char	**ft_split(const char *s, char c);
void	exepipe(char **cmd1, char **cmd2, char **envp, char **av);
char	*ft_strdup(const char *s1);
char	*my_strjoin(char *str1, char *str2);
char	*find_path(char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
int		check_file(char *str);
char	**assign_arg(char *av);


#endif