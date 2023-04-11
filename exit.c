#include "minishell.h"

int		check_digit(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (!(ft_isdigit((int)*tmp)))
			return (0);
		tmp++;
	}
	return (1);
}

int	builtin_exit(t_token **p_tok)
{
	int		status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if ((*p_tok)->next == 0)
		exit (0);
	if ((*p_tok)->next->next)
	{
		if ((*p_tok)->next->next->kind == 0)
		{
			ft_putendl_fd("exit: too many arguments", STDOUT_FILENO);
			g_global.status = 1;
		}
		return (0);
	}
	if (check_digit((*p_tok)->next->word))
	{
		status = ft_atoi((*p_tok)->next->word);
		if (status < 256)
			exit (status);
		else if (status > 255)
			exit (status - 256);
	}
	exit(255);
}
