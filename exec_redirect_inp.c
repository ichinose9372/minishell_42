#include "minishell.h"

void	remake_token(t_token **p_tok)
{
	t_token	*tmp;
	t_token	*third;
	t_token	**p_tmp;

	if ((*p_tok)->next->kind == 3)
	{
		tmp = *p_tok;
		p_tok = &(*p_tok)->next;
		third = (*p_tok)->next;
		tmp->next = third->next;
		third->next = tmp;
	}
	else
	{
		p_tmp = p_tok;
		while ((*p_tok)->kind == 0)
			p_tok = &(*p_tok)->next;
		third = (*p_tok)->next->next;
		tmp = (*p_tok)->next;
		while ((*p_tmp)->kind == 0)
		{
			tmp->next = (*p_tmp);
			tmp = tmp->next;
			p_tmp = &(*p_tmp)->next;
		}
		tmp->next = third;
	}

}

void	exec_redirect_inp(t_token **p_tok)
{
	int		file_fd;
	t_token	**tmp;

	if (ft_strncmp((*p_tok)->word, "<", 1) == 0)
	{
		file_fd = file_open_rd((*p_tok)->next->word);
		p_tok = &(*p_tok)->next->next;
		exec_cmd(p_tok, file_fd, STDOUT_FILENO);
	}
	else
	{
		tmp = p_tok;
		while ((*tmp)->kind == 0)
			tmp = &(*tmp)->next;
		file_fd = file_open_rd((*tmp)->next->word);
		remake_token(p_tok);
		exec_cmd(p_tok, file_fd, STDOUT_FILENO);
	}
}
