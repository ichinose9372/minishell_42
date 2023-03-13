/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:58:43 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/10 11:52:54 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	command_not_found(char *str)
{
	ft_putstr_fd("command not found: ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}

void	all_free(char **env_split)
{
	int	i;

	i = 0;
	while (env_split[i])
	{
		free(env_split[i]);
		i++;
	}
	free(env_split);
}

void	all_free_and_tmp(char *tmp, char **env_split)
{
	all_free(env_split);
	free(tmp);
}
