#include "minishell.h"

void	*malloc_error(size_t size)
{
	void	*str;

	str = malloc(size);
	if (!str)
	{
		ft_putendl_fd("malloc error", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	return (str);
}
