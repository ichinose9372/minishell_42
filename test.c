#include "minishell.h"

void	print_token(t_token **p_tok)
{
	t_token	**tmp;

	tmp = p_tok;
	while (*tmp)
	{
		printf("[%s]\n", (*tmp)->word);
		tmp = &(*tmp)->next;
	}
}