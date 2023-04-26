/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:49:16 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/26 14:49:17 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	double_expansion(char **dest, char *src)
{
	size_t	cnt;
	size_t	last_cnt;
	char	*tmp;

	cnt = 0;
	last_cnt = 0;
	while (src[cnt] != '\"')
	{
		if (src[cnt] == '$')
		{
			tmp = new_strjoin(*dest, &src[last_cnt], cnt - last_cnt);
			free(*dest);
			*dest = tmp;
			cnt += variable_expansion(dest, &src[cnt]);
			last_cnt = cnt;
		}
		else
			cnt++;
	}
	tmp = new_strjoin(*dest, &src[last_cnt], cnt - last_cnt);
	free(*dest);
	*dest = tmp;
	return (cnt + 2);
}

static size_t	single_expansion(char **dest, char *src)
{
	size_t	cnt;
	char	*tmp;

	cnt = 0;
	while (src[cnt] != '\'')
		cnt++;
	tmp = new_strjoin(*dest, src, cnt);
	free(*dest);
	*dest = tmp;
	return (cnt + 2);
}

size_t	char_expansion(char **dest, char *src)
{
	char	*tmp;

	tmp = new_strjoin(*dest, src, 1);
	free(*dest);
	*dest = tmp;
	return (1);
}

void	expansion(t_token *tok, t_token **p_tok)
{
	char	*new_word;
	size_t	cnt;

	*p_tok = tok;
	while (tok)
	{
		new_word = NULL;
		cnt = 0;
		while (tok->word[cnt])
		{
			if (tok->word[cnt] == '\"')
				cnt += double_expansion(&new_word, &tok->word[cnt + 1]);
			else if (tok->word[cnt] == '\'')
				cnt += single_expansion(&new_word, &tok->word[cnt + 1]);
			else if (tok->word[cnt] == '$')
				cnt += variable_expansion(&new_word, &tok->word[cnt]);
			else
				cnt += char_expansion(&new_word, &tok->word[cnt]);
		}
		free(tok->word);
		if (!new_word)
			new_word = ft_calloc(1, 1);
		tok->word = new_word;
		tok = tok->next;
	}
}
