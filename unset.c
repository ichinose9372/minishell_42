#include "minishell.h"

static void	del_env(t_env **tmp, t_env *prev)
{
	t_env	*del;

	del = *tmp;
	tmp = &(*tmp)->next;
	if (prev == NULL)
	{
		*g_global.env = *tmp;
		free(del->name);
		free(del->value);
		free(del);
		return ;
	}
	else
		prev->next = *tmp;
	free(del->name);
	free(del->value);
	free(del);
}

int	builtin_unset(t_token **p_tok)
{
	t_env	**tmp;
	t_env	*prev;
	t_token	*tok;

	prev = NULL;
	tok = *p_tok;
	if (tok->next == NULL)
		return (0);
	while (tok->next && tok->next->kind == 0)
	{
		tmp = g_global.env;
		while (*tmp)
		{
			if (ft_strncmp((*tmp)->name, tok->next->word,
					ft_strlen(tok->next->word) + 1) == 0)
				{
					del_env(tmp, prev);
					break ;
				}
			else
			{
				prev = *tmp;
				tmp = &(*tmp)->next;
			}
		}
		tok = (tok)->next;
	}
	return (0);
}
