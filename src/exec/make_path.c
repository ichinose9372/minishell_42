/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:49:53 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/07 14:24:13 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found(char *str)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd("command not found", 1);
	g_global.status = 127;
}

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

	if (tmp == NULL)
		return (NULL);
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

	if (argv[0] == '\0')
	{
		command_not_found(argv);
		return (NULL);
	}
	env_split = envp_make_path();
	if (env_split == NULL)
	{
		command_not_found(argv);
		return (NULL);
	}
	tmp = ft_strjoin("/", argv);
	path = serch_path(tmp, env_split);
	if (path == NULL)
	{
		all_free_and_tmp(tmp, env_split);
		return (NULL);
	}
	all_free_and_tmp(tmp, env_split);
	return (path);
}

char	**in_exec_path(char **args)
{
	char	*tmp;
	int		i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '/') != NULL && args[i][0] != '/')
		{
			tmp = create_absolute_path(args[i]);
			args[i] = ft_strdup(tmp);
		}
		i++;
	}
	tmp = *args;
	args[0] = make_path(tmp);
	free(tmp);
	return (args);
}
