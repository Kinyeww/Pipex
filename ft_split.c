#include "pipex.h"
#include <stdlib.h>

static char	*ft_putword(const char *s, int len, int start)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_counter(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**ft_dosplit(char **str, const char *s, char c, int	*filled)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[j] != c && s[j])
			j++;
		str[*(filled)] = ft_putword(s, (j - i), i);
		if (!(str[*filled]))
			return (NULL);
		(*filled)++;
		i = j;
	}
	return (str);
}

char	**ft_split(const char *s, char c)
{
	int		size;
	char	**str;
	int		filled;

	filled = 0;
	size = ft_counter(s, c);
	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (NULL);
	if (!(ft_dosplit(str, s, c, &filled)))
	{
		while (--filled >= 0)
			free (str[filled]);
		free (str);
	}
	str[filled] = NULL;
	return (str);
}
