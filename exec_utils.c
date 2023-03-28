#include "minishell.h"

int	builtin_list(t_token **p_tok)
{
	printf("test\n");
	if (ft_strncmp((*p_tok)->word, "pwd", 4) == 0)
		return (builtin_pwd(p_tok));
	else if (ft_strncmp((*p_tok)->word, "echo", 5) == 0)
		return (builtin_echo(p_tok));
	else if (ft_strncmp((*p_tok)->word, "env", 5) == 0)
		return (builtin_env(p_tok));
	else if (ft_strncmp((*p_tok)->word, "export", 5) == 0)
		return (builtin_export(p_tok));
	return (1);
}