/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:45:33 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/03/09 17:57:31 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>

# define READ	0
# define WRITE	1

typedef struct s_data
{
	pid_t	pid[2];
	int		error_num;
	int		status;
	char	**split_arg;
	int		p_fd[2];
	int		f_fd;
}	t_data;

//make_path
char	**envp_make_path(char **envp);
char	*make_path(char *split_arg, char **envp);
char	**split_arg(char *argv, char **envp);
void	pipe_init(t_data *px);
int		file_open_wrt(char *argv);
int		file_open_rd(char	*argv);
void	chiled_1(char **argv, t_data *px, char **envp);
void	chiled_2(char **argv, t_data *px, char **envp);
void	check_arg(char	*argv, t_data *px, char	**envp);
char	*serch_path(char	*tmp, char **env_split);
	// error
void	all_free(char **env_split);
void	all_free_and_tmp(char *tmp, char **env_split);
void	command_not_found(char *str);

#endif
