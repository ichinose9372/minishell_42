/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:01 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/21 16:48:47 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_cd(void)
{
	char	*new_path;
	char	path_name[PATH_SIZE];

	new_path = home_path();
	if (chdir(new_path) == -1)
	{
		free(new_path);
		perror("chdir");
		return (1);
	}
	free(new_path);
	remake_pwd(getcwd(path_name, PATH_SIZE));
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
	if ((args[0] && args[1] == NULL) || (args[0]
			&& args[1][0] == '~' && !args[1][1]))
		return (g_global.status = only_cd());
	if (args[0] && args[1])
		return (g_global.status = absolute_move(args[1]));
	return (0);
}
