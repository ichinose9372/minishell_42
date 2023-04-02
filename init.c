#include "minishell.c"

void	init_minishell(void)
{
	global.env = make_env();
	global.status = 0;
	global.our_environ = environ;
}
