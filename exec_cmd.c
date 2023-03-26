#include "minishell.h"

int	check_no_operation(t_token **p_tok)
{
	t_token	**tmp;
	int		ret;

	tmp = p_tok;
	ret = 0;
	while ((*tmp))
	{
		if (ft_strncmp((*tmp)->word, "|", 1) == 0)
		{
			ret = 1;
			return (ret);
		}
		else if (ft_strncmp((*tmp)->word, ">", 1) == 0)
		{
			if (ft_strncmp((*tmp)->word, ">>", 2) == 0)
			{
				ret = 3;
				return (ret);
			}
			else
			{
				ret = 2;
				return (ret);
			}
		}
		else if (ft_strncmp((*tmp)->word, "<", 1) == 0)
		{
			ret = 4;
			return (ret);
		}
		tmp = &(*tmp)->next;
	}
	return (ret);
}

void do_cmd(t_token **p_tok, int input_fd, int output_fd)
{
	char	**path;
	int		fd[2];
	pid_t	pid;
	int		f_fd;
	t_token	**tmp;

	if (check_no_operation(p_tok) == 1)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (input_fd != STDIN_FILENO)
				dup2(input_fd, STDIN_FILENO);
			close(fd[READ]);
			dup2(fd[WRITE], STDOUT_FILENO);
			close(fd[WRITE]);
			path = token_path(p_tok);
			execve(path[0], path, environ);
			perror("exec");
			exit(EXIT_FAILURE);
		}
		if (pid > 0)
		{
			close(fd[WRITE]);
			while (ft_strncmp((*p_tok)->word, "|", 1) != 0)
				p_tok = &(*p_tok)->next;
			p_tok = &(*p_tok)->next;
			do_cmd(p_tok, fd[READ], output_fd);
			close(fd[READ]);
			waitpid(pid, NULL, 0);
		}
	}
	else if (check_no_operation(p_tok) == 0)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (input_fd != 0)
				dup2(input_fd, STDIN_FILENO);
			if (output_fd != 1)
				dup2(output_fd, STDOUT_FILENO);
			// if (!ft_strncmp((*p_tok)->word, "pwd", 4))
			// {
			// 	printf("test\n");
			// 	builtin_pwd(p_tok);
			// }
			path = token_path(p_tok);
			execve(path[0], path, environ);
			perror("exec");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
			waitpid(pid, NULL, 0);
	}
	else if (check_no_operation(p_tok) == 2 || check_no_operation(p_tok) == 3)
	{
		tmp = p_tok;
		if (check_no_operation(p_tok) == 3)
		{
			while (ft_strncmp((*p_tok)->word, ">>", 2) != 0)
				p_tok = &(*p_tok)->next;
			p_tok = &(*p_tok)->next;
			f_fd = file_open_wrt_add((*p_tok)->word);
		}
		else
		{
			while (ft_strncmp((*p_tok)->word, ">", 1) != 0)
				p_tok = &(*p_tok)->next;
			p_tok = &(*p_tok)->next;
			f_fd = file_open_wrt((*p_tok)->word);
		}
		if (input_fd != 0)
			dup2(input_fd, STDIN_FILENO);
		dup2(f_fd, STDOUT_FILENO);
		path = token_path(tmp);
		execve(path[0], path, environ);
	}
	else if (check_no_operation(p_tok) == 4)
	{
		if (ft_strncmp((*p_tok)->word, "<", 1) == 0)
		{
			f_fd = file_open_rd((*p_tok)->next->word);
			dup2(f_fd, STDIN_FILENO);
			p_tok = &(*p_tok)->next->next;
			path = token_path(p_tok);
			execve(path[0], path, environ);
		}
		else
		{
			tmp = p_tok;
			while (ft_strncmp((*p_tok)->word, "<", 1) != 0)
				p_tok = &(*p_tok)->next;
			p_tok = &(*p_tok)->next;
			f_fd = file_open_rd((*p_tok)->word);
			if (output_fd != 1)
				dup2(output_fd, STDOUT_FILENO);
			dup2(f_fd, STDIN_FILENO);
			path = token_path(tmp);
			execve(path[0], path, environ);
		}
	}
}
