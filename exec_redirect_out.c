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
	int		builtin;
	char	**path;

	tmp = p_tok;
	file_fd = ft_open(p_tok);
	if (file_fd == 0)
		return ;
	if (input_fd != 0)
		dup2(input_fd, STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	builtin = builtin_list(p_tok);
	if (builtin == 1)
	{
		path = token_path(p_tok);
		pid = fork();
		if (pid == 0)
			exec(path);
		else if (pid > 0)
		{
			wait(NULL);
			all_free(path);
		}

	}
	else if (builtin == -1)
	{
		ft_putendl_fd("builtin error", 1);
		g_global.status = 1;
	}
	else if (builtin == 0)
		g_global.status = 0;
}
