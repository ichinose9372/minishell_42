#include "minishell.h"

void	handler_cmd(int sig)
{
	if (sig == 3)
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_global.status = 128 + sig;
}

void	signal_cmd(void)
{
	signal(SIGINT, handler_cmd);
	signal(SIGQUIT, handler_cmd);
}
