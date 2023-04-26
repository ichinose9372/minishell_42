/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:14 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/26 14:48:18 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_check(char *str, int start)
{
	return (str[start] == ' ' || str[start] == '\t' || str[start] == '\n');
}

int	operater_cmp(char *str, int end)
{
	if (ft_strncmp(&str[end], "|", 1) == 0)
		return (1);
	else if (ft_strncmp(&str[end], "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(&str[end], ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(&str[end], "<", 1) == 0)
		return (1);
	else if (ft_strncmp(&str[end], ">", 1) == 0)
		return (1);
	return (0);
}

t_token	*new_token(char *str, int start, int end)
{
	t_token	*tok;

	tok = (t_token *)malloc_error(sizeof(t_token));
	tok->word = new_strdup(&str[start], end - start);
	tok->old_word = new_strdup(&str[start], end - start);
	if (!tok->word)
		exit(0);
	tok->next = NULL;
	return (tok);
}

char	*new_strdup(const char *s1, int size)
{
	char	*dest;
	char	*src;
	int		cnt;

	src = (char *)s1;
	dest = (char *)malloc_error(sizeof(char) * (size + 1));
	cnt = 0;
	while (cnt < size)
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	dest[cnt] = '\0';
	return (dest);
}

void	token_kind(t_token *tok)
{
	if (ft_strncmp(tok->word, "|", 2) == 0)
		tok->kind = PIPE;
	else if (ft_strncmp(tok->word, ">>", 3) == 0)
		tok->kind = ADD;
	else if (ft_strncmp(tok->word, ">", 2) == 0)
		tok->kind = OUTPUT;
	else if (ft_strncmp(tok->word, "<<", 3) == 0)
		tok->kind = HEREDOC;
	else if (ft_strncmp(tok->word, "<", 2) == 0)
		tok->kind = INPUT;
	else
		tok->kind = WORD;
}
