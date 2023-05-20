/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:01 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/20 14:52:44 by yichinos         ###   ########.fr       */
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
	if (len == 0)
		new_path = ft_strdup("/");
	else
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

char	*other_move(char *path_name, char *word)
{
	char	*new_path;

	new_path = cd_make_path(path_name, word);
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

int	path_cd(char *args)
{
	char	**tmp;
	int		i;

	i = 0;
	if (args[0] == '/')
		return (absolute_move(args));
	tmp = ft_split(args, '/');
	while (tmp[i])
	{
		if (in_path_cd(tmp[i]))
		{
			all_free(tmp);
			return (1);
		}
		i++;
	}
	all_free(tmp);
	return (0);
}

int	builtin_cd(char	**args)
{
	if (args[0] && args[1])
	{
		if (args[1][0] == '.' && args[1][1] == '\0')
			return (0);
	}
	if (serch_home())
	{
		ft_putendl_fd("cd: HOME not set", 1);
		return (1);
	}
	if ((args[0] && args[1] == NULL) || (args[0] && args[1][0] == '~'))
		return (g_global.status = only_cd());
	if (args[0] && args[1])
		return (g_global.status = path_cd(args[1]));
	return (0);
}
