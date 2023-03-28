#include "minishell.h"

void	env_sort(t_token *tmp);

int	builtin_export(t_token **p_tok)
{
	t_env *tmp;

	tmp = *env;
	printf("test1\n");
	if ((*p_tok)->next == NULL || operater_cmp((*p_tok)->next->word, 0) != 0)
	{
		while (tmp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"\n", 1);
			tmp = tmp->next;
		}
	}
	return (0);
}