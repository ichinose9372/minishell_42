#include "minishell.h"

int	builtin_list(t_token **p_tok)
{
	if (ft_strncmp((*p_tok)->word, "pwd", 4) == 0)
		return (builtin_pwd(p_tok));
	else if (ft_strncmp((*p_tok)->word, "echo", 5) == 0)
		return (builtin_echo(p_tok));
	else if (ft_strncmp((*p_tok)->word, "env", 4) == 0)
		return (builtin_env(p_tok));
	else if (ft_strncmp((*p_tok)->word, "export", 7) == 0)
		return (builtin_export(p_tok));
	else if (ft_strncmp((*p_tok)->word, "unset", 6) == 0)
		return (builtin_unset(p_tok));
	else if (ft_strncmp((*p_tok)->word, "exit", 5) == 0)
		return (builtin_exit(p_tok));
	return (1);
}

void	exec(char	**path)
{
	execve(path[0], path, environ);
	perror("exec");
	exit (1);
}
