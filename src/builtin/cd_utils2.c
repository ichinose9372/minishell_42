/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:11:19 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/13 16:56:42 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_path_cd(char *tmp)
{
	char	path_name[PATH_SIZE];
	char	*new_path;

	my_getcwd(path_name, PATH_SIZE);
	if (ft_strncmp(tmp, ".", 2) == 0)
		;
	else if ((ft_strncmp(tmp, "..", 3) == 0))
	{
		new_path = prev_move(path_name);
		if (new_path == NULL)
			return (1);
		remake_pwd(new_path);
	}
	else
	{
		new_path = other_move(path_name, tmp);
		if (new_path == NULL)
			return (1);
		remake_pwd(new_path);
	}
	return (0);
}

int	absolute_move(char *args)
{
	char	*tmp;

	tmp = ft_strdup(args);
	if (chdir(tmp) == -1)
	{
		perror("chdir");
		return (1);
	}
	remake_pwd(tmp);
	return (0);
}
