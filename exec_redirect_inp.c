#include "minishell.h"

void	exec_redirect_inp(t_token **p_tok, int output_fd)
{
	t_token	**tmp;
	int		file_fd;
	pid_t	pid;

	tmp = p_tok;
	if (ft_strncmp((*p_tok)->word, "<", 1) == 0)
	{
		file_fd = file_open_rd((*p_tok)->next->word);
		p_tok = &(*p_tok)->next->next;
		exec_cmd(p_tok, file_fd, STDOUT_FILENO);
	}
	else
	{
		while (ft_strncmp((*p_tok)->word, "<", 1) != 0)
			p_tok = &(*p_tok)->next;
		p_tok = &(*p_tok)->next;
		file_fd = file_open_rd((*p_tok)->word);
		if (output_fd != 1)
			dup2(output_fd, STDOUT_FILENO);
		dup2(file_fd, STDIN_FILENO);
		if (builtin_list(p_tok) == 1)
		{
			pid = fork();
			if (pid == 0)
				exec(tmp);
			else if (pid != 0)
			{
				wait(NULL);
				close(file_fd);
			}
		}
	}
}
