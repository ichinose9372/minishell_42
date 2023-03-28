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
			if (ft_strncmp((*tmp)->word, "<<", 2) == 0)
			{
				ret = 5;
				return (ret);
			}
			ret = 4;
			return (ret);
		}
		else if (ft_strncmp((*tmp)->word, "<<", 2) == 0)
		{
			ret = 5;
			return (ret);
		}
		tmp = &(*tmp)->next;
	}
	return (ret);
}

void	do_cmd(t_token **p_tok, int input_fd, int output_fd)
{
	char	**path;
	int		fd[2];
	pid_t	pid;
	int		f_fd;
	t_token	**tmp;
	char	*str;
	char	*str2;
	char	*tmp_str;
	char	*c;

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
			if (builtin_list(p_tok) == 1)
			{
				path = token_path(p_tok);
				execve(path[0], path, environ);
				perror("exec");
			}
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
			if (builtin_list(p_tok) == 1)
			{
				path = token_path(p_tok);
				execve(path[0], path, environ);
				perror("exec");
			}
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
		if (builtin_list(tmp) == 1)
		{
			path = token_path(tmp);
			execve(path[0], path, environ);
		}
	}
	else if (check_no_operation(p_tok) == 4)
	{
		if (ft_strncmp((*p_tok)->word, "<", 1) == 0)
		{
			f_fd = file_open_rd((*p_tok)->next->word);
			p_tok = &(*p_tok)->next->next;
			do_cmd(p_tok, f_fd, 1);
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
	else if (check_no_operation(p_tok) == 5)
	{
		pid = fork();
		if (pid == 0)
		{
			tmp = p_tok;
			while (ft_strncmp((*tmp)->word, "<<", 2) != 0)
				tmp = &(*tmp)->next;
			pipe(fd);
			c = "\n";
			str2 = malloc(sizeof(char) * 1);
			while (1)
			{
				str = readline("> ");
				if (ft_strncmp(str, (*tmp)->next->word, ft_strlen(str)) == 0)
					break ;
				tmp_str = ft_strjoin(str, c);
				str2 = ft_strjoin(str2, tmp_str);
			}
			write(fd[1], str2, ft_strlen(str2));
			dup2(fd[0], STDIN_FILENO);
			path = token_path(p_tok);
			close(fd[0]);
			close(fd[1]);
			execve(path[0], path, environ);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
	}
}
