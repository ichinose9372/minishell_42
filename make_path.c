#include "minishell.h"

char	**envp_make_path(void)
{
	t_env	**tmp;
	char	*serch;
	char	**env_split;

	serch = "PATH";
	tmp = &(*global.env);
	while (ft_strncmp((*tmp)->name, serch, 4) != 0)
		tmp = &(*tmp)->next;
	env_split = ft_split((*tmp)->value, ':');
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
	char	*trim;
	char	*path;
	char	*tmp;

	env_split = envp_make_path();
	if (env_split == NULL)
	{
		command_not_found(argv);
		return (NULL);
	}
	trim = "/";
	tmp = ft_strjoin(trim, argv);
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

char	**token_path(t_token **p_tok)
{
	char	**argv;
	int		i;
	int		size;
	t_token	**tmp_tok;

	tmp_tok = p_tok;
	size = 0;
	while ((*tmp_tok))
	{
		if (ft_strncmp((*tmp_tok)->word, "|", 1) == 0
			|| ft_strncmp((*tmp_tok)->word, ">", 1) == 0
			||ft_strncmp((*tmp_tok)->word, ">>", 2) == 0
			||ft_strncmp((*tmp_tok)->word, "<<", 2) == 0
			|| ft_strncmp((*tmp_tok)->word, "<", 2) == 0)
			break ;
		size++;
		tmp_tok = &(*tmp_tok)->next;
	}
	argv = malloc(sizeof(char *) * (size + 1));
	if (argv == NULL)
		return (NULL);
	tmp_tok = p_tok;
	i = 0;
	while (i < size)
	{
		argv[i] = ft_strdup((*tmp_tok)->word);
		if (argv[i] == NULL)
			return (NULL); // argv全部をフリーする。
		i++;
		tmp_tok = &(*tmp_tok)->next;
	}
	argv[size] = NULL;
	if (ft_strchr(argv[0], '/') != 0)
		return (argv);
	else
	{
		argv[0] = make_path(argv[0]);
		if (argv[0] == NULL)
			return (NULL);
		return (argv);
	}
}
