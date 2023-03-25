
#include "minishell.h"

int	space_check(char *str, int start)
{
	return (str[start] == ' ' || str[start] == '\t' || str[start] == '\n');
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

	(void) start;
	c = str[*end];
	*end += 1;
	while (str[*end] != '\0' && str[*end] != c)
		*end += 1;
	if (str[*end] == '\0')
		return (1);
	return (0);
}

void	make_token(t_token **tok, char *str, int start, int end)
{
	if ((*tok)->word == NULL)
	{
		(*tok)->word = new_strdup(&str[start], end - start);
		if (!(*tok)->word)
			exit(0);
	}
	else
	{
		(*tok)->next = new_token(str, start, end);
		*tok = (*tok)->next;
	}
	(*tok)->next = NULL;
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
			if (str[end] == '\'' || str[end] == '\"')
			{
				if (seartch_quote(str, start, &end))
					exit(0);
			}
			end++;
		}
		if (str[start] != '\0')
			make_token(&tok, str, start, end);
	}
	return (tmp);
}
