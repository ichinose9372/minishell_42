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

void	exec_cmd(t_token **p_tok, int input_fd, int output_fd)
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

void	do_cmd(t_token **p_tok, int input_fd, int output_fd)
{
	if (check_no_operation(p_tok) == 1)
		exec_pipe(p_tok, input_fd, output_fd);
	else if (check_no_operation(p_tok) == 0)
		exec_cmd(p_tok, input_fd, output_fd);
	else if (check_no_operation(p_tok) == 2 || check_no_operation(p_tok) == 3)
		exec_redirect_out(p_tok, input_fd);
	else if (check_no_operation(p_tok) == 4)
		exec_redirect_inp(p_tok, output_fd);
	else if (check_no_operation(p_tok) == 5)
		exec_heardocu(p_tok);
}
