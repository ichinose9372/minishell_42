/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:49:33 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/30 15:11:28 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	acces_check_file(char *argv)
{
	struct stat	stat_buf;

	stat(argv, &stat_buf);
	if (stat_buf.st_size >= 65536)
		return (-1);
	else
		return (1);
}

int	file_open_rd(char	*argv)
{
	int	fd;

	argv = create_absolute_path(argv);
	if (acces_check_file(argv) == -1)
	{
		free(argv);
		perror("error");
		g_global.status = 1;
		return (-1);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free(argv);
		perror("error");
		g_global.status = 1;
		return (-1);
	}
	free(argv);
	return (fd);
}

int	file_open_wrt(char	*argv)
{
	int	fd;

	argv = create_absolute_path(argv);
	fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(argv);
		perror("error");
		g_global.status = 1;
		return (-1);
	}
	free(argv);
	return (fd);
}

int	file_open_wrt_add(char	*argv)
{
	int	fd;

	argv = create_absolute_path(argv);
	fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		free(argv);
		perror("error");
		g_global.status = 1;
		return (-1);
	}
	free(argv);
	return (fd);
}
