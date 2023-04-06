#include "minishell.h"

void remake_token(t_token **p_tok)
{
	t_token	*tmp;
	t_token	*third;

	tmp = *p_tok;
	third = (*p_tok)->next->next;
	p_tok = &(*p_tok)->next;
	tmp->next = third->next;
	third->next = tmp;
}

void	exec_redirect_inp(t_token **p_tok)
{
	int		file_fd;

	if (ft_strncmp((*p_tok)->word, "<", 1) == 0)
	{
		file_fd = file_open_rd((*p_tok)->next->word);
		p_tok = &(*p_tok)->next->next;
		exec_cmd(p_tok, file_fd, STDOUT_FILENO);
	}
	else
	{
		file_fd = file_open_rd((*p_tok)->next->next->word);
		remake_token(p_tok);
		exec_cmd(p_tok, file_fd, STDOUT_FILENO);
	}
}
