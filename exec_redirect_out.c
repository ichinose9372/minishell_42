#include "minishell.h"

int	ft_open(t_token **p_tok)
{
	int	check_num;
	int	file_fd;

	check_num = check_operation(p_tok);
	if (check_num == 3)
	{
		while ((*p_tok)->kind != 4)
			p_tok = &(*p_tok)->next;
		if ((*p_tok)->next == NULL)
		{
			perror("open");
			exit(1);
		}
		p_tok = &(*p_tok)->next;
		file_fd = file_open_wrt_add((*p_tok)->word);
	}
	else
	{
		while ((*p_tok)->kind != 2)
			p_tok = &(*p_tok)->next;
		if ((*p_tok)->next == NULL)
		{
			perror("open");
			exit(1);
		}
		p_tok = &(*p_tok)->next;
		file_fd = file_open_wrt((*p_tok)->word);
	}
	return (file_fd);
}

void	exec_redirect_out(t_token **p_tok, int input_fd)
{
	int		file_fd;
	pid_t	pid;
	int		builtin;
	char	**path;
	t_token	**tmp;
	char	buf[1];

	tmp = p_tok;
	while ((*tmp)->next != NULL)
	{
		file_fd = ft_open(tmp);
		if (file_fd == 0)
			return ;
		while ((*tmp)->kind == 0)
			tmp = &(*tmp)->next;
		tmp = &(*tmp)->next;
	}
	if (input_fd != 0)
		dup2(input_fd, STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	builtin = builtin_list(p_tok);
	if (builtin == 1)
	{
		if ((*p_tok)->kind != 0 && (*p_tok)->kind == 2)
		{
			while (read(STDIN_FILENO, &buf, 1) > 0)
				write(file_fd, &buf, 1);
			close(STDIN_FILENO);
			close(file_fd);
			if ((*p_tok)->next->next != NULL)
				exec_cmd(&(*p_tok)->next->next, 0, 1);
		}
		else
		{
			path = token_path(p_tok);
			if (!path)
				return ;
			pid = fork();
			if (pid == 0)
				exec(path);
			else if (pid > 0)
			{
				wait(NULL);
				all_free(path);
				while ((*p_tok)->kind == 0)
					p_tok = &(*p_tok)->next;
				p_tok = &(*p_tok)->next;
				if ((*p_tok)->next != NULL)
				{
					dup2(g_global.fd_in, STDIN_FILENO);
					dup2(g_global.fd_out, STDOUT_FILENO);
					p_tok = &(*p_tok)->next->next;
					exec_cmd(p_tok, 1, 0);
				}
			}
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
