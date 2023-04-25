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
		if ((p_tok)->kind != WORD)
			set_fd(&p_tok, in, out);
		else
			str[i++] = ft_strdup(p_tok->word);
		p_tok = p_tok->next;
		if (*in < 0 || *out < 0)
			break ;
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
		g_global.status = 1;
		ft_putendl_fd("builtin error", STDERR_FILENO);
	}
	exit(g_global.status);
}

void	exe_parent(char	**args, t_token **p_tok, int input_fd, int *status)
{
	*status = -1;
	all_free(args);
	while ((*p_tok) && (*p_tok)->kind != PIPE)
			p_tok = &(*p_tok)->next;
	if ((*p_tok))
		p_tok = &(*p_tok)->next;
	exec_cmd(p_tok, input_fd, g_global.fd_out, status);

void	fork_and_cmd(char **args, t_pipe *pipe_data,
						int input_fd, int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (input_fd < 0 || output_fd < 0)
			exit (1);
		if (pipe_data->flag == 1)
			close(pipe_data->pipe_fd[READ]);
		exe_chiled(args, input_fd, output_fd);
	}
	else if (pid > 0)
		return ;
}

void	exec_cmd(t_token **p_tok, int input_fd, int output_fd, int *status)
{
	char	**args;
	t_pipe	pipe_data;
	int		child_status;

	args = NULL;
	if (!(*p_tok))
		return ;
	if (pipe_check(p_tok, &pipe_data))
		init_pipe_setfd(&output_fd, &pipe_data);
	args = sec_cmd(*p_tok, &input_fd, &output_fd);
	if (g_global.heredoc_flag == 1)
		return (heredoc_stop(args));
	if (!pipe_data.flag && builtin_check(args))
		return (swich_fd_check_builtin(input_fd, output_fd, args, status));
	if (args != NULL && !builtin_check(args) && ft_strchr(args[0], '/') == 0)
		args = in_exec_path(args);
	fork_and_cmd(args, &pipe_data, input_fd, output_fd);
	if (pipe_data.flag)
		close(pipe_data.pipe_fd[WRITE]);
	exe_parent(args, p_tok, pipe_data.pipe_fd[READ], status);
	if (pipe_data.flag)
		close_pipe(&pipe_data);
	wait(&child_status);
	if (*status == -1)
		g_global.status = WEXITSTATUS(child_status);
	else
		g_global.status = *status;
}
