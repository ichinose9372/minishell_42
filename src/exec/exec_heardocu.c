/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heardocu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:49:30 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/03 15:56:28 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_stop(t_token *stop)
{
	size_t	cnt;

	cnt = 0;
	if (stop->old_word[0] == '\"' || stop->old_word[0] == '\"')
		cnt++;
	if (stop->word[0] != stop->old_word[cnt])
	{
		if (cnt == 1)
			return (new_strdup(&(stop->old_word[cnt]),
					ft_strlen(stop->old_word) - 2));
		return (ft_strdup(stop->old_word));
	}
	return (ft_strdup(stop->word));
}

char	*heredoc_join(char *dest, char *rl)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(rl, "\n");
	str2 = ft_strjoin(dest, str1);
	free(rl);
	free(dest);
	free(str1);
	return (str2);
}

static char	*make_str(char	*stop)
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	str = NULL;
	while (g_global.heredoc_flag == 0)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strncmp(str, stop, (ft_strlen(stop) + 1)) == 0)
		{
			free(str);
			return (tmp);
		}
		expansion_heredoc(&str);
		tmp = heredoc_join(tmp, str);
	}
	return (tmp);
}

static char	*heredocu(t_token *p_tok)
{
	char	*str;
	char	*stop;

	stop = check_stop(p_tok);
	str = make_str(stop);
	free(stop);
	return (str);
}

int	heredoc_cmd(t_token *p_tok)
{
	t_pipe	pipe_data;
	char	*str;

	g_global.heredoc_flag = 0;
	signal_heredocu();
	str = heredocu(p_tok);
	if (str == NULL)
		return (-1);
	if (g_global.heredoc_flag == 1)
	{
		free(str);
		return (-2);
	}
	if (str && ft_strlen(str) >= 65536)
	{
		perror("pipe");
		return (-1);
	}
	if (pipe(pipe_data.pipe_fd) == -1)
		exit (EXIT_FAILURE);
	write(pipe_data.pipe_fd[WRITE], str, ft_strlen(str));
	free(str);
	close(pipe_data.pipe_fd[WRITE]);
	return (pipe_data.pipe_fd[READ]);
}
