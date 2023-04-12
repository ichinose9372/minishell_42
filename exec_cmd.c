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

void	exec_no_operat(t_token **p_tok, int input_fd, int output_fd)
{
	pid_t	pid;
	int		status;
	char	**path;
	int		builtin;

	signal_cmd();
	builtin = builtin_list(p_tok);
	if (builtin == 1)
	{
		path = token_path(p_tok);
		if (path == NULL)
			return ;
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			if (input_fd != 0)
				dup2(input_fd, STDIN_FILENO);
			if (output_fd != 1)
				dup2(output_fd, STDOUT_FILENO);
			exec(path);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				g_global.status = WEXITSTATUS(status);
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

// void	exec_cmd(t_token **p_tok, int input_fd, int output_fd)
// {
// 	if (p_tok == NULL)
// 		return ;
// 	if (check_operation(p_tok) == 1)
// 		exec_pipe(p_tok, input_fd, output_fd);
// 	else if (check_operation(p_tok) == 0)
// 		exec_no_operat(p_tok, input_fd, output_fd);
// 	else if (check_operation(p_tok) == 2 || check_operation(p_tok) == 4)
// 		exec_redirect_out(p_tok, input_fd);
// 	else if (check_operation(p_tok) == 3)
// 		exec_redirect_inp(p_tok);
// 	else if (check_operation(p_tok) == 5)
// 		exec_heardocu(p_tok);
// 	return ;
// }

void	sec_cmd(t_token **p_tok, char **args, int *in, int *out)
{
	int	i;

	i = 0;
	while ((*p_tok)->kind != PIPE || (*p_tok) == NULL)
	{
		if ((*p_tok)->kind == INPUT)
		{
			*p_tok = (*p_tok)->next;
			 in = openする。
		}
		else if ((*p_tok)->kind == OUTPUT)
		{
			*p_tok =  (*p_tok)->next;
			out = openする。
		}
		else if ((*p_tok)->kind == ADD)
		{
			*p_tok =  (*p_tok)->next;
			out = openする。
		}
		else if ((*p_tok)->kind == HEREDOC)
		{
			*p_tok = ((*p_tok)->next;
			pipefd = heredoucu(); pipeのfdの[read] がinputになる。
		}
		else
			args[i++] = ft_strdup((*p_tok)->word);
		*p_tok = *p_tok->next;
	}
}

 void	exec_cmd(t_token **p_tok, int input_fd, int output_fd)
 {
	char	**args;
	int		in;
	int		out;

	while ((*p_tok))
	{
		if ((*p_tok)->kind != PIPE)
		{
			dup2(pipe[read], STDIN_FILENO);
			dup2(g_global.fd_out, STDOUT_FILENO);
		}
		sec_cmd(p_tok, args, &in, &out); //p_tok進める。　argsを作る。　inと　outのfdを書き換える
		if ((*p_tok)->kind != PIPE)
	 	{
			pipi()
			dup2(pipe[write], STDOUT_FILENO);
		}
		else
			dup2(out ,STDOUT_FILENO);
		dup2(in ,STDIN_FILENO);
		execute(args);//
		all_free(args);
	}
 }
