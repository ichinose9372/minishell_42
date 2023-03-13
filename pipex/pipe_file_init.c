/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_file_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:50:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/09 17:52:49 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	file_open_rd(char	*argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	file_open_wrt(char	*argv)
{
	int	fd;

	fd = open(argv, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	pipe_init(t_data *px)
{
	px->pid[0] = 0;
	px->pid[1] = 0;
	if (pipe(px->p_fd) < 0)
		exit(EXIT_FAILURE);
}
