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
			set_fd(p_tok, in, out);
		else
			str[i++] = ft_strdup(p_tok->word);
		if (*in < 0 || *out < 0)
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

void	exe_parent(char	**args, t_token **p_tok, int input_fd)
{
	all_free(args);
	while ((*p_tok) && (*p_tok)->kind != PIPE)
			p_tok = &(*p_tok)->next;
	if ((*p_tok))
		p_tok = &(*p_tok)->next;
	exec_cmd(p_tok, input_fd, g_global.fd_out);
}

// void	fork_and_cmd(char **args, t_pipe *pipe_data, int input_fd, int output_fd)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == -1)
// 		exit(EXIT_FAILURE);
// 	if (pid == 0)
// 	{
// 		if (g_global.flag == 1)
// 			close(pipe_data->pipe_fd[READ]);
// 		exe_chiled(args, input_fd, output_fd);
// 	}
// 	else if (pid > 0)
// 		return ;
// }

void	exec_cmd(t_token **p_tok, int input_fd, int output_fd)
{
	char	**args;
	t_pipe	pipe_data;
	pid_t	pid;
	int		status;
	int		flag;

	args = NULL;
	flag = 0;
	if (!(*p_tok))
		return ;
	if (pipe_check(p_tok))
		init_pipe_setfd(&flag, &output_fd, &pipe_data);
	args = sec_cmd(*p_tok, &input_fd, &output_fd);
	if (g_global.heredoc_flag == 1)
	{
		g_global.heredoc_flag = 0;
		all_free(args);
		return ;
	}
	if (!flag && builtin_check(args))
	{
		swich_fd_check_builtin(input_fd, output_fd, args);
		return ;
	}
	if (args != NULL && !builtin_check(args) && ft_strchr(args[0], '/') == 0)
		args[0] = in_exec_path(args[0]);
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
		if (flag)
			close(pipe_data.pipe_fd[WRITE]);
		exe_parent(args, p_tok, pipe_data.pipe_fd[READ]);
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
