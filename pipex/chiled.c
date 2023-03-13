/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chiled.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:51:56 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/03/09 19:02:29 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	chiled_1(char **argv, t_data *px, char **envp)
{
	char	buf[1];

	px->f_fd = file_open_rd(argv[1]);
	if (argv[2] && argv[2][0] != '\0')
	{
		check_arg(argv[2], px, envp);
		close(px->p_fd[READ]);
		dup2(px->f_fd, STDIN_FILENO);
		dup2(px->p_fd[WRITE], STDOUT_FILENO);
		px->error_num = execve(px->split_arg[0], px->split_arg, envp);
		perror("exec");
	}
	else
	{
		while (read(px->f_fd, &buf, STDOUT_FILENO) > 0)
			write(px->p_fd[WRITE], &buf, STDOUT_FILENO);
		close(px->f_fd);
		close(px->p_fd[WRITE]);
		exit(EXIT_SUCCESS);
	}
}

void	chiled_2(char **argv, t_data *px, char	**envp)
{
	char	buf[1];

	px->f_fd = file_open_wrt(argv[4]);
	if (argv[3] && argv[3][0] != '\0')
	{
		check_arg(argv[3], px, envp);
		close(px->p_fd[WRITE]);
		dup2(px->p_fd[READ], STDIN_FILENO);
		dup2(px->f_fd, STDOUT_FILENO);
		close(px->f_fd);
		px->error_num = execve(px->split_arg[0], px->split_arg, envp);
		perror("exec");
	}
	else
	{
		close(px->p_fd[1]);
		while (read(px->p_fd[STDIN_FILENO], &buf, STDOUT_FILENO) > 0)
			write(px->f_fd, &buf, STDOUT_FILENO);
		close(px->f_fd);
		close(px->p_fd[READ]);
		exit(EXIT_SUCCESS);
	}
}

void	check_arg(char	*argv, t_data *px, char	**envp)
{
	if (ft_strchr(argv, '/') == 0)
	{
		px->split_arg = split_arg(argv, envp);
		if (px->split_arg == NULL)
			exit(EXIT_FAILURE);
	}
	else
	{
		px->split_arg = ft_split(argv, ' ');
		if (px->split_arg == NULL)
			exit(EXIT_FAILURE);
	}
}
