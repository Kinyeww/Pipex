#include "pipex.h"
#include <stdlib.h>
#include <fcntl.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s1cpy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s1cpy = malloc(sizeof(char) * (i + 1));
	if (!s1cpy)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s1cpy[i] = s1[i];
		i++;
	}
	s1cpy[i] = '\0';
	return (s1cpy);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_strdup(envp[i] + 5));
		i++;
	}
	return (NULL);
}

static char	*ft_malloc(char *str1, char *str2)
{
	int		i;
	int		k;
	char	*tmp;

	if (!str1 || !str2)
		return (NULL);
	i = 0;
	k = 0;
	while (str1[i])
		i++;
	while (str2[k])
		k++;
	tmp = malloc(sizeof(char) * ((i + k) + 2));
	return (tmp);
}

char	*my_strjoin(char *str1, char *str2)
{
	char	*tmp;
	int		i;
	int		k;

	tmp = ft_malloc(str1, str2);
	if (!tmp)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		tmp[i] = str1[i];
		i++;
	}
	tmp[i] = '/';
	i++;
	k = 0;
	while (str2[k])
	{
		tmp[i + k] = str2[k];
		k++;
	}
	tmp[i + k] = '\0';
	return (tmp);
}