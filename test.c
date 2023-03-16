/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:12:27 by stakimot          #+#    #+#             */
/*   Updated: 2023/03/16 15:49:57 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_token
{
	char			*word;
	struct s_token	*next;
}	t_token;

typedef enum e_token_quote
{
	OUT_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_token_quote;

char	*ft_strdup(const char *s1, int size)
{
	char	*dest;
	char	*src;
	size_t	cnt;

	src = (char *)s1;
	// cnt = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	cnt = 0;
	while (cnt < size)
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	dest[cnt] = '\0';
	return (dest);
}

int	space_check(char *str, int start)
{
	return (str[start] == ' ' || str[start] == '\t' || str[start] == '\n');
}

int	operater_check(char *str, int start)
{
	if (str[start] == '|')
		return (1);
	return (0);
}

int	seartch_quote(char *str, int start, int *end)
{
	*end += 1;
	while (str[*end] && str[*end]!= str[start])
		*end += 1;
	if (str[*end] == '\0')
		return (1);
	return (0);
}

t_token	*new_token(char *str, int start, int end)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (0);
	tok->word = ft_strdup(&str[start], end - start);
	if (!tok->word)
		return (0);
	tok->next = NULL;
	return (tok);
}

void	make_token(t_token **tok, char *str, int start, int end)
{
	// if (operater_check(str, start))
	// {
	// 	end++;
	*tok = new_token(str, start, end);
	*tok = (*tok)->next;
	// }
	// if (start == end)
	// {
	// 	end += operater_check(str, start);
	// 	tok = new_token(str, start, end);
	// 	tok = (*tok)->next;
	// }
}

void	print_stack(t_token **tok)
{
	while(1)
	{
		printf("%s\n", (*tok)->word);
		if ((*tok)->next == NULL)
			break ;
		*tok = (*tok)->next;
	}
	return ;
}

t_token	*tokenizer(char *str)
{
	t_token			*tok;
	int				start;
	int				end;

	start = 0;
	end = 0;
	while (str[start])
	{
		printf("test!\n");
		while (str[end] != '\0' && !space_check(str, start))
		{
			printf("test\n");
			// if (operater_check(str, start))
			// 	break ;
			// if (str[start] == '\'' || str[start] == '\"')
			// 	if (search_quote(str, start, &end))
			// 		exit (0);
			end++;
		}
		make_token(&tok, str, start, end);
		while(space_check(str, end))
			end++;
		start = end;
	}
	print_stack(&tok);
	return (tok);
}

int	main(void)
{
	// printf("%d\n", space_check(" a", 1));
	tokenizer("a sd fgh");
}
