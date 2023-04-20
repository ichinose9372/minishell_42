#include "minishell.h"

int	builtin_env(char **args)
{
	t_env	*tmp;

	(void)args;
	tmp = *g_global.env;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
