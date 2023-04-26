/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:49:18 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/26 14:49:19 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operation(t_token **p_tok)
{
	t_token	**tmp;
	int		ret;

	tmp = p_tok;
	ret = 0;
	while ((*tmp))
	{
		if ((*tmp)->kind != 0)
			return ((*tmp)->kind);
		tmp = &(*tmp)->next;
	}
	return (ret);
}

bool	pipe_check(t_token **p_tok, t_pipe *pipe_data)
{
	pipe_data->flag = 0;
	while ((*p_tok))
	{
		if ((*p_tok)->kind == PIPE)
			return (true);
		p_tok = &(*p_tok)->next;
	}
	return (false);
}

int	count(t_token *p_tok)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = p_tok;
	while (tmp)
	{
		if (tmp->kind != WORD)
			tmp = tmp->next;
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	close_pipe(t_pipe *pipe_data)
{
	close(pipe_data->pipe_fd[READ]);
	close(pipe_data->pipe_fd[WRITE]);
}

void	heredoc_stop(char **args)
{
	g_global.heredoc_flag = 0;
	all_free(args);
	return ;
}
