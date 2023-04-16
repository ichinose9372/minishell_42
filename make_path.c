#include "minishell.h"

char	**envp_make_path(void)
{
	t_env	*tmp;
	char	*serch;
	char	**env_split;

	serch = "PATH";
	tmp = *g_global.env;
	while (tmp && ft_strncmp(tmp->name, serch, 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	env_split = ft_split(tmp->value, ':');
	if (env_split == NULL)
		return (NULL);
	return (env_split);
}

char	*serch_path(char	*tmp, char **env_split)
{
	char	*path;

	while (*env_split)
	{
		path = ft_strjoin(*env_split, tmp);
		if (path == NULL)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		env_split++;
		free(path);
	}
	command_not_found(tmp);
	return (NULL);
}

char	*make_path(char *argv)
{
	char	**env_split;
	char	*path;
	char	*tmp;

	env_split = envp_make_path();
	if (env_split == NULL)
	{
		command_not_found(argv);
		return (NULL);
	}
	tmp = ft_strjoin("/", argv);
	if (tmp == NULL)
	{
		all_free(env_split);
		return (NULL);
	}
	path = serch_path(tmp, env_split);
	if (path == NULL)
	{
		all_free_and_tmp(tmp, env_split);
		return (NULL);
	}
	all_free_and_tmp(tmp, env_split);
	return (path);
}
