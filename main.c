/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:12:27 by stakimot          #+#    #+#             */
/*   Updated: 2023/03/15 02:55:54 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_token
{
	char			*word;
	struct s_token	*next;
}	t_token;

typedef enum e_token_kind
{
	NOMAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_token_kind;

int	check_space(char c, t_token_kind *kind)
{
	if (kind != NOMAL)
		return (0);
	else if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\'')
		*kind = SINGLE_QUOTE;
	else if (c == '\"')
		*kind = DOUBLE_QUOTE;
	else
		return (0);
	return (0);
}

t_token	*tokenizer(char *str)
{
	t_token	*tok;
	t_token_kind kind;
	int		cnt;

	kind = NOMAL;
	cnt = 0;
	while (str[cnt])
	{
		if (check_space(str[cnt], &kind))
			continue;
	}
	printf("%d\n", kind);
	return (tok);
}

int	main(void)
{
	tokenizer(" ");
}
