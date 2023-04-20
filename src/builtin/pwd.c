#include "minishell.h"

int	builtin_pwd(char **args)
{
	char	path_name[PATH_SIZE];

	(void)args;
	if (!my_getcwd(path_name, PATH_SIZE))
		return (-1);
	ft_putendl_fd(path_name, STDOUT_FILENO);
	return (0);
}
