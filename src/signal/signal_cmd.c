/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:46 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/30 16:22:06 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_cmd(int sig)
{
	if (sig == 3)
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_global.status = 128 + sig;
}

void	signal_cmd(void)
{
	signal(SIGINT, handler_cmd);
	signal(SIGQUIT, handler_cmd);
}
