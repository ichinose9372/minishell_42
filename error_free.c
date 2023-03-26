/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:58:43 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/26 01:21:15 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	all_free_token(t_token **p_tok)
{
	// size_t	i;
	t_token	*tmp;

	// i = 0;
	while ((*p_tok))
	{
		tmp = (*p_tok)->next;
		free((*p_tok));
		*p_tok = tmp;
	}
	p_tok = NULL;
}

void	all_free_and_tmp(char *tmp, char **env_split)
{
	all_free(env_split);
	free(tmp);
}
