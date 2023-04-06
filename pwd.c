#include "minishell.h"

int	builtin_pwd(t_token	**p_tok)
{
	char	path_name[PATH_SIZE];

	(void)p_tok;
	if (!my_getcwd(path_name, PATH_SIZE))
		return (-1);
	ft_putendl_fd(path_name, 1);
	return (0);
}
