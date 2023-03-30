#include "minishell.h"

void	signal_one_c(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_one()
{
	printf("test\n");
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_one_c);
}