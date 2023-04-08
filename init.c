#include "minishell.h"

t_global	global;

void	init_minishell(void)
{
	extern char	**environ;

	global.env = make_env();
	global.status = 0;
	global.fd_in = dup(STDIN_FILENO);
	global.fd_out = dup(STDOUT_FILENO);
}
