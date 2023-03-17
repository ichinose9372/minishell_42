/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:12:27 by stakimot          #+#    #+#             */
/*   Updated: 2023/03/17 16:03:51 by stakimot         ###   ########.fr       */
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

char	*new_strdup(const char *s1, int size)
{
	char	*dest;
	char	*src;
	size_t	cnt;

	src = (char *)s1;
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cnt;

	cnt = 0;
	while (cnt < n && (s1[cnt] != '\0' || s2[cnt] != '\0'))
	{
		if (s1[cnt] != s2[cnt])
			return ((unsigned char)s1[cnt] - (unsigned char)s2[cnt]);
		cnt++;
	}
	return (0);
}
t_token	*new_token(char *str, int start, int end)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (0);
	tok->word = new_strdup(&str[start], end - start);
	if (!tok->word)
		exit (0);
	return (tok);
}

void	make_token(t_token **tok, char *str, int start, int end)
{
	*tok = (*tok)->next;
	*tok = new_token(str, start, end);
	printf("%s\n", (*tok)->word);
}

int	operater_comp(char *str, int end)
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
	else if (ft_strncmp(&str[end], ";", 1) == 0)
		return (1);
	return (0);
}

int	operater_check(char *str, int *start, int *end, t_token **tok)
{
	if (operater_comp(str, *end))
	{
		if (*start != *end)
			return (1);
		else
			*end += operater_comp(str, *end);
	}
	else
		return (0);
	make_token(tok, str, *start, *end);
	while (space_check(str, *end))
		*end += 1;
	*start = *end;
	return (0);
}

int	seartch_quote(char *str, int start, int *end)
{
	char	c;

	c = str[*end];
	*end += 1;
	while (str[*end] != '\0' && str[*end] != c)
		*end += 1;
	if (str[*end] == '\0')
		return (1);
	return (0);
}


t_token	*tokenizer(char *str)
{
	t_token	*tok;
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (str[start])
	{
		while (str[end] != '\0' && !space_check(str, end))
		{
			if (operater_check(str, &start, &end, &tok))
				break ;
			if (str[end] == '\'' || str[end] == '\"')
			{
				if (seartch_quote(str, start, &end))
					exit(0);
			}
			end++;
		}
		make_token(&tok, str, start, end);
		while(str[end] != '\0' && space_check(str, end))
			end++;
		start = end;
	}
	return (tok);
}

int	main(void)
{
char *str = "\"hello w\"\'orld\'; cat<file|wc";

	t_token	*tok;
	tok = tokenizer(str);
	// printf("%s\n", tok->word);
}
