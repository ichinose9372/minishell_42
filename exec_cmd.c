#include "minishell.h"

int	check_no_operation(t_token **p_tok)
{
	t_token	**tmp;
	int		ret;

	tmp = p_tok;
	ret = 0;
	while ((*tmp))
	{
		if ((*tmp)->kind != 0)
			return ((*tmp)->kind);
		tmp = &(*tmp)->next;
	}
	return (ret);
}

void	exec_no_operat(t_token **p_tok, int input_fd, int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (input_fd != 0)
			dup2(input_fd, STDIN_FILENO);
		if (output_fd != 1)
			dup2(output_fd, STDOUT_FILENO);
		exec(p_tok);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}

void	exec_cmd(t_token **p_tok, int input_fd, int output_fd)
{
	if (check_no_operation(p_tok) == 1)
		exec_pipe(p_tok, input_fd, output_fd);
	else if (check_no_operation(p_tok) == 0)
		exec_no_operat(p_tok, input_fd, output_fd);
	else if (check_no_operation(p_tok) == 2 || check_no_operation(p_tok) == 4)
		exec_redirect_out(p_tok, input_fd);
	else if (check_no_operation(p_tok) == 3)
		exec_redirect_inp(p_tok, output_fd);
	else if (check_no_operation(p_tok) == 5)
<<<<<<< HEAD
		exec_heardocu(p_tok);
=======
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
				signal_heredoc();
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
>>>>>>> a046845a1dc1b97490a7f0827851167a9fea9669
}
