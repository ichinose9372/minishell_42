#include "minishell.h"

t_global	global;

void	init_minishell(void)
{
	extern char	**environ;

	global.env = make_env();
	global.status = 0;
	global.our_environ = environ;
}
