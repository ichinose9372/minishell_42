// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   many_pipe.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/16 20:59:49 by ichinoseyuu       #+#    #+#             */
// /*   Updated: 2023/03/18 17:46:28 by ichinoseyuu      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

// // int	cheak_arg(char *argv)
// // {
// // 	while (argv)
// // 	{
// // 		if (*argv == '>')
// // 			return (1);
// // 		else if (*argv == '<')
// // 			return (-1);
// // 		else
// // 			argv++;
// // 	}
// // 	return (0);
// // }

// // void	open_file(char *argv)
// // {
// // 	if (cheak_arg(argv) == 1)
// // 		file_open_wrt(argv + 1);
// // 	if (cheak_arg(argv) == -1)
// // 		file_open_rd(argv - 1);
// // }

// // void	dopipes(int argc, char	**argv, char **envp)
// // {
// // 	char	**path;
// // 	int		fd[2];
// // 	pid_t	pid_pid;

// // 	if (argc == 2)
// // 	{
// // 		path = split_arg(argv[argc - 1], envp);
// // 		execve(path[0], path, envp);
// // 	}
// // 	else
// // 	{
// // 		pipe(fd);
// // 		pid_pid = fork();
// // 		if (pid_pid == 0)
// // 		{
// // 			close(fd[0]);
// // 			dup2(fd[1], STDOUT_FILENO);
// // 			close(fd[1]);
// // 			argc--;
// // 			dopipes(argc, argv, envp);
// // 		}
// // 		else if (pid_pid > 0)
// // 		{
// // 			argc--;
// // 			close(fd[1]);
// // 			dup2(fd[0], STDIN_FILENO);
// // 			close(fd[0]);
// // 			path = split_arg(argv[argc], envp);
// // 			execve(path[0], path, envp);
// // 		}
// // 	}
// // }

// // void dopipes(int argc, char **argv, char **envp)
// // {
// // 	char	**path;
// // 	int		fd[2];
// // 	pid_t	pid_pid;
// // 	int		f_fd;
// // 	char	**env_path;
// // 	char	buf[1];

// // 	env_path = envp_make_path(envp);
// // 	if (argc == 2)
// // 	{
// // 		if (argv[argc + 2] && argv[argc + 1][0] == '>')
// // 		{
// // 			f_fd = file_open_wrt(argv[argc + 2]);
// // 			dup2(f_fd, STDOUT_FILENO);
// // 		}
// // 		else if (argv[argc - 1] && argv[argc -2][0] == '<')
// // 		{
// // 			f_fd = file_open_rd(argv[argc - 2]);
// // 			dup2(f_fd, STDIN_FILENO);
// // 		}
// // 		if (!(split_arg(argv[argc - 1], envp)))
// // 			exit(1);
// // 		path = split_arg(argv[argc - 1], envp);
// // 		execve(path[0], path, envp);
// // 	}
// // 	else
// // 	{
// // 		pipe(fd);
// // 		pid_pid = fork();
// // 		if (pid_pid == 0)
// // 		{
// // 			close(fd[0]);
// // 			dup2(fd[1], STDOUT_FILENO);
// // 			close(fd[1]);
// // 			argc--;
// // 			dopipes(argc, argv, envp);
// // 		}
// // 		else if (pid_pid > 0)
// // 		{
// // 			if (!(split_arg(argv[argc -1], envp)))
// // 				exit(1);
// // 			f_fd = file_open_rd(argv[argc - 2]);
// // 			while (read(f_fd, &buf, 1) > 0)
// // 				write(fd[1], &buf, 1);
// // 			close(f_fd);
// // 			close(fd[1]);
// // 			dup2(fd[0], STDIN_FILENO);
// // 			close(fd[0]);
// // 			path = split_arg(argv[argc -1], envp);
// // 			execve(path[0], path, envp);
// // 		}
// // 	}
// // }

// void	dopipes(int argc, char **argv, char **envp)
// {
// 	int		fd[2];
// 	pid_t	pid_pid;
// 	char	**path;

// 	if (argc == 2)
// 	{
// 		path = split_arg(argv[argc - 1], envp);
// 		if (path[0] == NULL)
// 			exit (EXIT_FAILURE);
// 		execve(path[0], path, envp);
// 	}
// 	else
// 	{
// 		argc--;
// 		pipe(fd);
// 		pid_pid = fork();
// 		if (pid_pid == 0)
// 		{
// 			dopipes(argc, argv, envp);
// 		}
// 		else if (pid_pid > 0)
// 		{
// 			path = split_arg(argv[argc - 1], envp);
// 			if (path[0] == NULL)
// 				exit(EXIT_FAILURE);
// 			execve(path[0], path, envp);
// 		}
// 	}
// }


// 	int main(int argc, char **argv, char **envp)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 		dopipes(argc, argv, envp);
// 	else if (pid > 0)
// 		wait(NULL);
// 	return (0);
// }
