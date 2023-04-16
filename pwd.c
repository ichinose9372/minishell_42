#include "minishell.h"

int	builtin_pwd(char **args)
{
	char	path_name[PATH_SIZE];

	(void)args;
	g_global.status = 0;
	if (!my_getcwd(path_name, PATH_SIZE))
		return (-1);
	ft_putendl_fd(path_name, STDOUT_FILENO);
	return (0);
}
