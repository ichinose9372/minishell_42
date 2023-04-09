#include "minishell.h"

t_token	*remake_token(t_token *tok)
{
	t_token	*cmd;
	t_token	*third;
	t_token	*tmp;

	if (tok->next->kind == 3)
	{
		cmd = tok;
		tok = tok->next;
		third = tok->next;
		cmd->next = third->next;
		third->next = cmd;
	}
	else
	{
		tmp = tok;
		while (tok->kind == 0)
			tok = tok->next;
		third = tok->next->next;
		cmd = tok->next;
		while (tmp->kind == 0)
		{
			cmd->next = tmp;
			cmd = cmd->next;
			tmp = tmp->next;
		}
		cmd->next = third;
	}
	return (tok);
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
		*p_tok = remake_token(*p_tok);
		exec_cmd(p_tok, STDIN_FILENO, STDOUT_FILENO);
	}
}
