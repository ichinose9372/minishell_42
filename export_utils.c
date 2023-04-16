#include "minishell.h"

int	export_elem_error(char *str)
{
	ft_putstr_fd("export: `", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putendl_fd("': not a valid identifier", STDOUT_FILENO);
	g_global.status = 1;
	return (1);
}