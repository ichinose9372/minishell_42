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

bool	pipe_check(t_token **p_tok)
{
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
