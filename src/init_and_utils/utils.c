#include "minishell.h"

void	*malloc_error(size_t size)
{
	void	*str;

	str = malloc(size);
	if (!str)
	{
		ft_putendl_fd("malloc error", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	*new_strjoin(char const *s1, char const *s2, size_t s2_len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (new_strdup(s2, s2_len));
	if (!s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc_error(ft_strlen(s1) + s2_len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	put_export_environ(t_env *tmp, char *str)
{
	if (ft_strcmp(str, "OLDPWD") == 0)
	{
		ft_putstr_fd("declare -x OLDPWD", STDOUT_FILENO);
		if (g_global.oldpwd != NULL)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(g_global.oldpwd, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
	}
	else if (tmp->value)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->name, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
			ft_putstr_fd(g_global.oldpwd, STDOUT_FILENO);
		else
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
		ft_putchar_fd('\"', STDOUT_FILENO);
	}
}
