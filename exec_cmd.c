#include "minishell.h"

int	check_operation(t_token **p_tok)
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

int		count(t_token *p_tok)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = p_tok;
	while (tmp)
	{
		if (tmp->kind != WORD)
			tmp = tmp->next;
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**sec_cmd(t_token *p_tok, int *in, int *out)
{
	char	**str;
	int		i;

	i = count(p_tok);
	str = malloc(sizeof(char *) * (i + 1));

	i = 0;
	while ((p_tok) && (p_tok)->kind != PIPE)
	{
		if ((p_tok)->kind == INPUT)
		{
			p_tok = (p_tok)->next;
			*in = file_open_rd((p_tok)->word);
		}
		else if ((p_tok)->kind == OUTPUT)
		{
			p_tok = (p_tok)->next;
			*out = file_open_wrt((p_tok)->word);
		}
		else if ((p_tok)->kind == ADD)
		{
			p_tok = (p_tok)->next;
			*out = file_open_wrt_add((p_tok)->word);
		}
		else if ((p_tok)->kind == HEREDOC)
		{
			p_tok = (p_tok)->next;
			*in = heredoc_cmd(&p_tok);
			// pipefd = heredoucu(); pipeのfdの[read] がinputになる。
		}
		else
		{
			str[i] = ft_strdup(p_tok->word);
			i++;
		}
		p_tok = (p_tok)->next;
	}
	str[i] = NULL;
	str[0] = make_path(str[0]);
	return (str);
}

void	exe_chiled(char	**args, int input_fd, int output_fd)
{
	int	builtin;

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
	{
		args[0] = make_path(args[0]);
		exec(args);
	}
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

	args = NULL;
	signal_cmd();
	if (!(*p_tok))
		return ;
	if (pipe_check(p_tok))
	{
		if (pipe(pipe_data.pipe_fd) == -1)
		{
			printf("!!! faled !!!\n");
			exit(EXIT_FAILURE);
		}
		output_fd = pipe_data.pipe_fd[WRITE];
	}
	args = sec_cmd(*p_tok, &input_fd, &output_fd);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipe_data.pipe_fd[READ]);
		exe_chiled(args, input_fd, output_fd);
	}
	else if (pid > 0)
	{
		close(pipe_data.pipe_fd[WRITE]);
		while ((*p_tok) && (*p_tok)->kind != PIPE)
			p_tok = &(*p_tok)->next;
		if ((*p_tok))
			p_tok = &(*p_tok)->next;
		exec_cmd(p_tok, pipe_data.pipe_fd[READ], g_global.fd_out);
		close(pipe_data.pipe_fd[READ]);
		close(pipe_data.pipe_fd[WRITE]);
		wait(NULL);
	}
}
