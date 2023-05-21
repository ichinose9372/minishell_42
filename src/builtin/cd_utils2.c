/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:11:19 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/21 16:52:29 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	absolute_move(char *args)
{
	char	path_name[PATH_SIZE];

	if (chdir(args) == -1)
	{
		perror("chdir");
		return (1);
	}
	remake_pwd(getcwd(path_name, PATH_MAX));
	return (0);
}
