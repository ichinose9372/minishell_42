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
	t_env	**tmp;

	tmp = g_global.env;
	while (*tmp && ft_strncmp((*tmp)->name, "PWD", 4) != 0)
		tmp = &(*tmp)->next;
	if (*tmp == NULL)
		return (NULL);
	size = 0;
	while (size < length - 1 && (*tmp)->value[size])
	{
		buf[size] = (*tmp)->value[size];
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


char	*prev_move(char	*path_name)
{
	char	*last;
	char	*new_path;
	size_t	len;
	int		ret;

	last = ft_strrchr(path_name, '/');
	len = ft_strlen(path_name) - ft_strlen(last);
	new_path = ft_substr(path_name, 0, len);
	if (!new_path)
		exit(1);
	ret = chdir(new_path);
	if (ret == -1)
	{
		perror("chdir");
		exit(1);
	}
	return (new_path);
}

char	*next_move(char *path_name, char *word)
{
	char	*new_path;

	new_path = make_next_path(path_name, word);
	printf("new_path = [ %s ]\n", new_path);
	if (chdir(new_path) == -1)
	{
		perror("chdir");
		free(new_path);
		return (NULL);
	}
	return (new_path);
}

int	only_cd(void)
{
	char	*new_path;

	new_path = home_path();
	if (chdir(new_path) == -1)
	{
		perror("chdir");
		return (0);
	}
	remake_pwd(new_path);
	free(new_path);
	return (0);
}

void	path_cd(char *path_name, char *args)
{
	char	*new_path;

	if (ft_strncmp(args, "..", 3) == 0)
	{
		new_path = prev_move(path_name);
		remake_pwd(new_path);
		free(new_path);
	}
	else
	{
		new_path = next_move(path_name, args);
		remake_pwd(new_path);
		free(new_path);
	}
}

int	builtin_cd(char	**args)
{
	char	path_name[PATH_SIZE];

	if (serch_home())
	{
		ft_putendl_fd("cd: HOME not set", 1);
		return (0);
	}
	if (!my_getcwd(path_name, PATH_SIZE))
		return (1);
	if (args[0] && args[1] == NULL)
	{
		only_cd();
		return (0);
	}
	if (args[0] && args[1])
		path_cd(path_name, args[1]);
	return (0);
}
