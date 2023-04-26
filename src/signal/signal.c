/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:36 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/26 14:48:39 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_one_c(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_global.status = 1;
}

void	signal_one(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_one_c);
}

void	handler_heredocu_c(int sig)
{
	(void)sig;
	g_global.heredoc_flag = 1;
	g_global.status = 1;
}

int	check_status(void)
{
	if (g_global.heredoc_flag == 1)
		rl_done = 1;
	return (0);
}

void	signal_heredocu(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_heredocu_c);
	rl_event_hook = check_status;
}
