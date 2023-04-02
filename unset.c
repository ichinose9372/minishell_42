#include "minishell.h"

int	builtin_unset(t_token **p_tok)
{
	t_env	**tmp;
	t_env	*del;
	t_env	*prev;

	tmp = global.env;
	prev = NULL;
	if ((*p_tok)->next == NULL)
		exit(EXIT_FAILURE);
	while (*tmp)
	{
		if (ft_strncmp((*tmp)->name, (*p_tok)->next->word,
				ft_strlen((*p_tok)->next->word)) == 0)
		{
			del = *tmp;
			tmp = &(*tmp)->next;
			if (prev == NULL)
				global.env = tmp;
			prev->next = *tmp;
			free(del->name);
			free(del->value);
			free(del);
		}
		else
		{
			prev = *tmp;
			tmp = &(*tmp)->next;
		}
	}
	return (0);
}
