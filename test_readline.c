/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:52:05 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/13 18:44:16 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipex/include/pipex.h"
#include <sys/wait.h>
#include <string.h>

extern char	**environ;

char	*del_quat(char *path)
{
	int		len;
	char	*new_str;

	len = ft_strlen(path);
	if (len > 2 && path[0] == '\'' && path[len - 1] == '\'')
	{
		new_str = malloc(sizeof(char) * (len - 1));
		strncpy(new_str, path + 1, len -2);
		new_str[len -2] = '\0';
		return (new_str);
	}
	else
		return (path);
}

char	**make_token(char **path)
{
	char	**tmp_path;

	tmp_path = path;
	while (*path)
	{
		*path = del_quat(*path);
		path++;
	}
	return (tmp_path);
}

void	do_cmd(char	*str)
{
	char	**path;
	char	*tmp;

	path = split_arg(str, environ);
	path = make_token(path);
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
