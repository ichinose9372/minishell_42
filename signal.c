#include "minishell.h"

void	handler_one_c(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_one()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_one_c);
}

void	handler_heredocu_c(int sig)
{
	(void)sig;
	global.heredoc_flag = 1;
	global.status = 1;
}

int	check_status(void)
{
	if (global.heredoc_flag == 1)
		rl_done = 1;
	return (0);
}

void	signal_heredocu()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_heredocu_c);
	rl_event_hook = check_status;
}

void	handler_cmd(int sig)
{
	if (sig == 3)
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	global.status = 128 + sig;
}

void	signal_cmd()
{
	signal(SIGINT, handler_cmd);
	signal(SIGQUIT, handler_cmd);
}