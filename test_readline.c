/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:52:05 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/15 11:48:49 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"
#include <sys/wait.h>
#include <string.h>

extern char	**environ;

void	do_cmd(char	*str)
{
	char	**path;

	path = split_arg(str, environ);
	execve(path[0], path, environ);
}

int	main(void)
{
	char	*str;
	pid_t	pid;
	int		status;

	while (1)
	{
		str = readline("mini_shell$ ");
		if (str == NULL)
			exit (1);
		else
		{
			add_history(str);
			pid = fork();
			if (pid == 0)
				do_cmd(str);
			else if (pid > 0)
				wait(&status);
			else
				exit(1);
		}
		free (str);
	}
	exit(0);
}
