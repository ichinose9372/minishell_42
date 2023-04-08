#include "minishell.h"

int	ft_open(t_token **p_tok)
{
	int	check_num;
	int	file_fd;

	check_num = check_operation(p_tok);
	if (check_num == 3)
	{
		while (ft_strncmp((*p_tok)->word, ">>", 2) != 0)
			p_tok = &(*p_tok)->next;
		p_tok = &(*p_tok)->next;
		file_fd = file_open_wrt_add((*p_tok)->word);
	}
	else
	{
		while (ft_strncmp((*p_tok)->word, ">", 1) != 0)
			p_tok = &(*p_tok)->next;
		p_tok = &(*p_tok)->next;
		file_fd = file_open_wrt_add((*p_tok)->word);
	}
	return (file_fd);
}

void	exec_redirect_out(t_token **p_tok, int input_fd)
{
	t_token	**tmp;
	int		file_fd;
	pid_t	pid;

	tmp = p_tok;
	file_fd = ft_open(p_tok);
	if (file_fd == 0)
		return ;
	if (input_fd != 0)
		dup2(input_fd, STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	if (builtin_list(p_tok) == 1)
	{
		pid = fork();
		if (pid == 0)
			exec(tmp);
		else if (pid > 0)
			wait(NULL);
	}
}
