#include "minishell.h"

int	builtin_list(t_token **p_tok)
{
	if (ft_strncmp((*p_tok)->word, "pwd", 4) == 0)
		return (builtin_pwd(p_tok));
	else if (ft_strncmp((*p_tok)->word, "echo", 4) == 0)
		return (builtin_echo(p_tok));
	else if (ft_strncmp((*p_tok)->word, "env", 3) == 0)
		return (builtin_env(p_tok));
	else if (ft_strncmp((*p_tok)->word, "export", 6) == 0)
		return (builtin_export(p_tok));
	else if (ft_strncmp((*p_tok)->word, "unset", 5) == 0)
		return (builtin_unset(p_tok));
	else if (ft_strncmp((*p_tok)->word, "exit", 5) == 0)
		return (builtin_exit(p_tok));
	return (1);
}

void	exec(t_token **p_tok)
{
	char	**path;
	int		builtin;

	builtin = builtin_list(p_tok);
	if (builtin == 1)
	{
		if ((*p_tok)->word[0] == '\0')
		{
			ft_putendl_fd("command not found", STDOUT_FILENO);
			global.status = 127;
			exit(global.status);
		}
		path = token_path(p_tok);
		if (path == NULL)
		{
			global.status = 127;
			exit(global.status);
		}
		execve(path[0], path, environ);
		perror("exec");
	}
	else if (builtin == 0)
	{
		global.status = 0;
		exit (global.status);
	}
	else if (builtin == -1)
	{
		ft_putendl_fd("builtin error", 1);
		global.status = 1;
		exit(global.status);
	}
}
