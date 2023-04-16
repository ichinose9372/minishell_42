#include "minishell.h"

char	**sec_cmd(t_token *p_tok, int *in, int *out)
{
	char	**str;
	int		i;

	signal_cmd();
	i = count(p_tok);
	str = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((p_tok) && (p_tok)->kind != PIPE)
	{
		if ((p_tok)->kind == INPUT)
			*in = set_input(&p_tok);
		else if ((p_tok)->kind == OUTPUT)
			*out = set_output(&p_tok);
		else if ((p_tok)->kind == ADD)
			*out = set_add(&p_tok);
		else if ((p_tok)->kind == HEREDOC)
		{
			p_tok = (p_tok)->next;
			*in = heredoc_cmd(p_tok);
			if ((*in == -1 && !p_tok->next) || *in == -2)
			{
				all_free(str);
				return (NULL);
			}
		}
		else
			str[i++] = ft_strdup(p_tok->word);
		if (*in == -1 || *out == -1)
		{
			all_free(str);
			return (NULL);
		}
		p_tok = (p_tok)->next;
	}
	str[i] = NULL;
	return (str);
}

void	exe_chiled(char	**args, int input_fd, int output_fd)
{
	int	builtin;

	if (args == NULL || args[0] == NULL)
		exit(EXIT_FAILURE);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	builtin = builtin_list(args);
	if (builtin == 1)
		exec(args);
	else if (builtin == -1)
	{
		ft_putendl_fd("builtin error", STDERR_FILENO);
	}
	exit(EXIT_SUCCESS);
}

void	exec_cmd(t_token **p_tok, int input_fd, int output_fd)
{
	char	**args;
	t_pipe	pipe_data;
	pid_t	pid;
	int		flag;
	int		status;
	char	*tmp;

	args = NULL;
	flag = 0;
	signal_cmd();
	if (!(*p_tok))
		return ;
	if (pipe_check(p_tok))
	{
		flag = 1;
		if (pipe(pipe_data.pipe_fd) == -1)
		{
			printf("!!! faled !!!\n");
			exit(EXIT_FAILURE);
		}
		output_fd = pipe_data.pipe_fd[WRITE];
	}
	args = sec_cmd(*p_tok, &input_fd, &output_fd);
	if (g_global.heredoc_flag == 1)
	{
		g_global.heredoc_flag = 0;
		all_free(args);
		return ;
	}
	if (!flag && builtin_check(args))
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		if (builtin_list(args) == 0)
		{
			g_global.status = 0;
			all_free(args);
			return ;
		}
		else
			g_global.status = 1;
	}
	if (args != NULL && !builtin_check(args) && ft_strchr(args[0], '/') == 0)
	{
		tmp = args[0];
		args[0] = make_path(args[0]);
		free(tmp);
		if (args[0] == NULL)
			exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (flag)
			close(pipe_data.pipe_fd[READ]);
		exe_chiled(args, input_fd, output_fd);
	}
	else if (pid > 0)
	{
		all_free(args);
		if (flag)
			close(pipe_data.pipe_fd[WRITE]);
		while ((*p_tok) && (*p_tok)->kind != PIPE)
			p_tok = &(*p_tok)->next;
		if ((*p_tok))
			p_tok = &(*p_tok)->next;
		exec_cmd(p_tok, pipe_data.pipe_fd[READ], g_global.fd_out);
		if (flag)
		{
			close(pipe_data.pipe_fd[READ]);
			close(pipe_data.pipe_fd[WRITE]);
		}
		if (WIFEXITED(status))
				g_global.status = WEXITSTATUS(status);
		wait(NULL);
	}
}
