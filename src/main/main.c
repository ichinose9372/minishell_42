/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:53 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/26 14:56:01 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check(t_token **p_tok)
{
	t_token	*tmp;

	tmp = *p_tok;
	if (tmp->kind == PIPE)
	{
		ft_putendl_fd("syntax error", STDOUT_FILENO);
		return (1);
	}
	while (tmp)
	{
		if ((tmp->kind != WORD && tmp->next && tmp->next->kind == tmp->kind) || \
			(tmp->kind != WORD && !tmp->next))
		{
			ft_putendl_fd("syntax error", STDOUT_FILENO);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	minishell_2(t_token **p_tok, char *str)
{
	t_token	*tok;
	int		status;

	status = -1;
	(void)p_tok;
	tok = malloc_error(sizeof(t_token));
	tok->word = NULL;
	tok->old_word = NULL;
	tok->next = NULL;
	tok = tokenizer(str, tok);
	if (tok == NULL)
		return (1);
	if (tok == NULL || tok->word == NULL)
	{
		free(tok);
		return (1);
	}
	expansion(tok, p_tok);
	if (syntax_check(p_tok))
		return (0);
	exec_cmd(p_tok, 0, 1, &status);
	return (0);
}

void	in_minishell(t_token **p_tok, char *str)
{
	add_history(str);
	if (minishell_2(p_tok, str) == 1)
		free(p_tok);
	else
		all_free_token(p_tok);
	free(str);
}

void	minishell(void)
{
	char	*str;
	t_token	**p_tok;

	while (1)
	{
		p_tok = (t_token **)malloc_error(sizeof(t_token *));
		signal_one();
		str = readline("minishell$ ");
		signal(SIGINT, SIG_IGN);
		if (str == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		else if (*str == '\0')
		{
			free(str);
			free(p_tok);
		}
		else
			in_minishell(p_tok, str);
		dup2(g_global.fd_in, STDIN_FILENO);
		dup2(g_global.fd_out, STDOUT_FILENO);
	}
	exit(0);
}

int	main(void)
{
	init_minishell();
	minishell();
}
