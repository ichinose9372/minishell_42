#include "minishell.h"

int	builtin_env(t_token **p_tok)
{
	t_env **tmp;

	printf("builtin\n");
	tmp = env;
	(void)p_tok;
	while (*tmp)
	{
		ft_putstr_fd((*tmp)->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd((*tmp)->value, 1);
		ft_putstr_fd("\n", 1);
		tmp = &(*tmp)->next;
	}
	printf("!!!!!env = %s\t%s\n", (*env)->name, (*env)->value);
	return (0);
}
