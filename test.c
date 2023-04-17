#include "minishell.h"

void	print_token(t_token **p_tok)
{
	t_token	**tmp;

	tmp = p_tok;
	while (*tmp)
	{
		printf("[w=%s]\n[ow=%s]\n", (*tmp)->word, (*tmp)->old_word);
		tmp = &(*tmp)->next;
	}
}
