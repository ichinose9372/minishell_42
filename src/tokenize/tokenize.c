/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:06 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/26 14:48:23 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operater_check(char *str, int *start, int *end, t_token **tok)
{
	if (operater_cmp(str, *end))
	{
		if (*start != *end)
			return (1);
		else
			*end += operater_cmp(str, *end);
	}
	else
		return (0);
	make_token(tok, str, *start, *end);
	while (space_check(str, *end))
		*end += 1;
	*start = *end;
	return (0);
}

int	seartch_quote(char *str, int start, int *end, t_token *tmp)
{
	char	c;

	(void) start;
	c = str[*end];
	*end += 1;
	while (str[*end] != '\0' && str[*end] != c)
		*end += 1;
	if (str[*end] == '\0')
	{
		ft_putendl_fd("quote error", STDERR_FILENO);
		g_global.status = 1;
		free_token(tmp);
		return (1);
	}
	return (0);
}

void	make_token(t_token **tok, char *str, int start, int end)
{
	if ((*tok)->word == NULL)
	{
		(*tok)->word = new_strdup(&str[start], end - start);
		(*tok)->old_word = new_strdup(&str[start], end - start);
	}
	else
	{
		(*tok)->next = new_token(str, start, end);
		*tok = (*tok)->next;
	}
	token_kind(*tok);
	(*tok)->next = NULL;
}

void	make_old_word(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		tmp->old_word = ft_strdup(tmp->word);
		tmp = tmp->next;
	}
}

t_token	*tokenizer(char *str, t_token *tok)
{
	t_token	*tmp;
	int		start;
	int		end;

	start = 0;
	end = 0;
	tmp = tok;
	while (str[start])
	{
		while (str[end] != '\0' && space_check(str, end))
			end++;
		start = end;
		while (str[end] != '\0' && !space_check(str, end))
		{
			if (operater_check(str, &start, &end, &tok))
				break ;
			if ((str[end] == '\'' || str[end] == '\"') \
				&& seartch_quote(str, start, &end, tmp))
				return (NULL);
			end++;
		}
		if (str[start] != '\0')
			make_token(&tok, str, start, end);
	}
	return (tmp);
}
