/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:52:05 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/20 14:01:25 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include <readline/readline.h>
// #include <readline/history.h>

// extern	char	**environ;

// void	do_cmd(char	*str)
// {
// 	char	**path;

// 	path = split_arg(str, environ);
// 	execve(path[0], path, environ);
// }


// int	main(void)
// {
// 	char	*str;
// 	pid_t	pid;
// 	int		status;
// 	int		i;
// 	t_token  *tok;


// 	tok = malloc(sizeof(t_token));
// 	rl_outstream = stderr;
// 	while (1)
// 	{
// 		str = readline("mini_shell$ ");
// 		if (str == NULL)
// 			exit (1);
// 		else
// 		{
// 			add_history(str);
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				tok = tokenizer(str, tok);
// 			}
// 			else if (pid > 0)
// 				wait(&status);
// 			else
// 				exit(1);
// 		}
// 		free (str);
// 	}
// 	exit (0);
// }
