/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:55 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/26 14:48:56 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **args)
{
	char	path_name[PATH_SIZE];

	(void)args;
	if (!my_getcwd(path_name, PATH_SIZE))
		return (-1);
	ft_putendl_fd(path_name, STDOUT_FILENO);
	g_global.status = 0;
	return (0);
}
