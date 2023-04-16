#include "minishell.h"

int	set_input(t_token **p_tok)
{
	int	in;

	*p_tok = (*p_tok)->next;
	in = file_open_rd((*p_tok)->word);
	return (in);
}

int	set_output(t_token **p_tok)
{
	int	out;

	*p_tok = (*p_tok)->next;
	out = file_open_wrt((*p_tok)->word);
	return (out);
}

int	set_add(t_token **p_tok)
{
	int	out;

	*p_tok = (*p_tok)->next;
	out = file_open_wrt_add((*p_tok)->word);
	return (out);
}
