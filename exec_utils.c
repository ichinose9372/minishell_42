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

	path = token_path(p_tok);
	if (path == NULL)
		exit(global.status);
	execve(path[0], path, environ);
	perror("exec");
	exit (1);
}
