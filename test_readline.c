/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:52:05 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/18 18:22:53 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

extern char	**environ;

void	do_cmd(char	*str)
{
	char	**path;

	path = split_arg(str, environ);
	execve(path[0], path, environ);
}

void dopipes(int argc, char **argv, char **envp)
{
	int fd[2];
	pid_t pid_pid;
	char **path;

	if (argc == 1)
	{
		path = split_arg(argv[argc - 1], envp);
		if (path[0] == NULL)
			exit(EXIT_FAILURE);
		execve(path[0], path, envp);
	}
	else
	{
		pipe(fd);
		pid_pid = fork();
		if (pid_pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			dopipes(argc - 1, argv, envp);
		}
		else if (pid_pid > 0)
		{
			argc--;
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			path = split_arg(argv[argc], envp);
			if (path[0] == NULL)
				exit(EXIT_FAILURE);
			execve(path[0], path, envp);
		}
	}
}

int	main(void)
{
	char	*str;
	pid_t	pid;
	int		status;
	char	**argv;
	int		i;

	rl_outstream = stderr;
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
			{
				argv = ft_split(str, ' ');
				i = 0;
				while (argv[i])
					i++;
				dopipes(i, argv, environ);
			}
			else if (pid > 0)
				wait(&status);
			else
				exit(1);
		}
		free (str);
	}
	exit (0);
}
