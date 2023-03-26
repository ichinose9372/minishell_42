#include "minishell.h"

bool	builtin_pwd(t_token	**p_tok)
{
	char	path_name[PATH_SIZE];

	(void)p_tok;
	if (!getcwd(path_name, PATH_SIZE))
		return (false);
	ft_putendl_fd(path_name, 1);
	return (true);
}
