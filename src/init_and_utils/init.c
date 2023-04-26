/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:49:09 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/26 14:49:10 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_minishell(void)
{
	g_global.env = make_env();
	g_global.status = 0;
	g_global.fd_in = dup(STDIN_FILENO);
	g_global.fd_out = dup(STDOUT_FILENO);
}
