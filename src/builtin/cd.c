/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:01 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/26 18:36:10 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prev_move(char	*path_name)
{
	char	*last;
	char	*new_path;
	size_t	len;

	last = ft_strrchr(path_name, '/');
	len = ft_strlen(path_name) - ft_strlen(last);
	new_path = ft_substr(path_name, 0, len);
	if (!new_path)
		return (NULL);
	if (chdir(new_path) == -1)
	{
		free(new_path);
		perror("chdir");
		return (NULL);
	}
	return (new_path);
}

char	*next_move(char *path_name, char *word)
{
	char	*new_path;

	new_path = make_next_path(path_name, word);
	if (chdir(new_path) == -1)
	{
		free(new_path);
		perror("chdir");
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
		free(new_path);
		perror("chdir");
		return (1);
	}
	remake_pwd(new_path);
	return (0);
}

int	path_cd(char *path_name, char *args)
{
	char	*new_path;

	if ((ft_strncmp(args, "..", 3) == 0) || ft_strncmp(args, "../", 4) == 0)
	{
		new_path = prev_move(path_name);
		if (new_path == NULL)
			return (1);
		remake_pwd(new_path);
	}
	else if (ft_strncmp(args, "./", 3) == 0)
		return (0);
	else
	{
		new_path = next_move(path_name, args);
		if (new_path == NULL)
			return (1);
		remake_pwd(new_path);
	}
	return (0);
}

int	builtin_cd(char	**args)
{
	char	path_name[PATH_SIZE];

	if (args[0] && (args[1][0] == '.' && args[1][1] == '\0'))
		return (0);
	if (serch_home())
	{
		ft_putendl_fd("cd: HOME not set", 1);
		return (1);
	}
	if (!my_getcwd(path_name, PATH_SIZE))
		return (1);
	if ((args[0] && args[1] == NULL) || (args[0] && args[1][0] == '~'))
		return (g_global.status = only_cd());
	if (args[0] && args[1])
		return (g_global.status = path_cd(path_name, args[1]));
	return (0);
}
