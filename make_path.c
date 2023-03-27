/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:41:12 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/03/26 16:18:35 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_make_path(char **envp)
{
	char	*serch;
	char	*trim_env;
	char	**env_split;

	serch = "PATH=";
	while (*envp)
	{
		if ((ft_strncmp(*envp, serch, ft_strlen(serch))) == 0)
			break ;
		envp++;
	}
	trim_env = ft_strtrim(*envp, serch);
	env_split = ft_split(trim_env, ':');
	if (env_split == NULL)
		return (NULL);
	free(trim_env);
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
	return (NULL);
}

char	*make_path(char *argv, char **envp)
{
	char	**env_split;
	char	*trim;
	char	*path;
	char	*tmp;

	env_split = envp_make_path(envp);
	if (env_split == NULL)
		return (NULL);
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
		if (ft_strncmp((*tmp_tok)->word, "|", 1) == 0 || ft_strncmp((*tmp_tok)->word, ">", 1) == 0 || ft_strncmp((*tmp_tok)->word, ">>", 2) == 0 || ft_strncmp((*tmp_tok)->word, "<<", 2) == 0 || ft_strncmp((*tmp_tok)->word, "<", 2) == 0)
			break ;
		size++;
		tmp_tok = &(*tmp_tok)->next;
	}
	argv = malloc(sizeof(char *) * (size + 1));
	tmp_tok = p_tok;
	i = 0;
	while (i < size)
	{
		argv[i] = ft_strdup((*tmp_tok)->word);
		i++;
		tmp_tok = &(*tmp_tok)->next;
	}
	argv[size] = NULL;
	argv[0] = make_path(argv[0], environ);
	return (argv);
}
