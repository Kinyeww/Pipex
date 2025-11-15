#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
//function name below
typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
}	t_pipex;

char	**check_arg(char *av);
char	**ft_split(const char *s, char c);
void	exepipe(t_pipex *pipex, char **envp, char **av);
char	*ft_strdup(const char *s1);
char	*my_strjoin(char *str1, char *str2);
char	*find_path(char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
int		check_file(char *str);
char	**assign_arg(char *av);
char	*find_abs_path(char *paths, char *cmd1);
void	close_program(t_pipex *pipex);
void	first_child(t_pipex *pipex, int pipefd[2], char **envp);
void	call_second_child(t_pipex *pipe, int pipefd[2], char **envp, char **av);
void	call_first_child(t_pipex *pipe, int pipefd[2], char **envp, char **av);
void	free_arr(char **str);

#endif