#include "minishell.h"

void	init_minishell(void)
{
	g_global.env = make_env();
	g_global.status = 0;
	g_global.fd_in = dup(STDIN_FILENO);
	g_global.fd_out = dup(STDOUT_FILENO);
}
