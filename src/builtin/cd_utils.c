#include "minishell.h"

char	*home_path(void)
{
	char	*home;
	t_env	**tmp;

	tmp = g_global.env;
	while (ft_strncmp((*tmp)->name, "HOME", 5) != 0)
		tmp = &(*tmp)->next;
	home = ft_strdup((*tmp)->value);
	if (home == NULL)
		return (NULL);
	return (home);
}

void	remake_pwd(char	*new_path)
{
	t_env	**tmp;
	size_t	size;

	tmp = g_global.env;
	while (ft_strncmp((*tmp)->name, "PWD", 4) != 0)
		tmp = &(*tmp)->next;
	size = 0;
	while (new_path[size])
	{
		(*tmp)->value[size] = new_path[size];
		size++;
	}
	(*tmp)->value[size] = '\0';
	free(new_path);
}

int	serch_home(void)
{
	t_env	*tmp;

	tmp = *g_global.env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "HOME", 5) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	*my_getcwd(char *buf, size_t length)
{
	size_t	size;
	t_env	*tmp;

	tmp = *g_global.env;
	while (tmp && ft_strncmp(tmp->name, "PWD", 4) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	size = 0;
	while (size < length - 1 && tmp->value[size])
	{
		buf[size] = tmp->value[size];
		size++;
	}
	buf[size] = '\0';
	return (buf);
}

char	*make_next_path(char *path_name, char	*word)
{
	char	*new_path;
	char	*tmp;

	if (word[0] == '/')
	{
		new_path = ft_strdup(word);
		if (!new_path)
			exit(1);
	}
	else
	{
		tmp = ft_strjoin("/", word);
		new_path = ft_strjoin(path_name, tmp);
		if (!new_path)
			exit(1);
		free(tmp);
	}
	return (new_path);
}
