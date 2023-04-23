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

int	unset_elem_check(char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt])
	{
		if ((cnt == 0 && !ft_isalpha(str[cnt]) && str[cnt] != '_') || \
			(cnt != 0 && !ft_isalnum(str[cnt]) && str[cnt] != '_'))
		{
			ft_putstr_fd("unset: `", STDOUT_FILENO);
			ft_putstr_fd(str, STDOUT_FILENO);
			ft_putendl_fd("': not a valid identifier", STDOUT_FILENO);
			g_global.status = 1;
			return (0);
		}
		cnt++;
	}
	return (1);
}

void	in_unset(char *str)
{
	t_env	**tmp;
	t_env	*prev;

	tmp = g_global.env;
	prev = NULL;
	while (*tmp)
	{
		if (ft_strncmp((*tmp)->name, str,
				ft_strlen(str) + 1) == 0)
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
	g_global.status = 0;
	return ;
}

int	builtin_unset(char **args)
{
	size_t	cnt;

	cnt = 1;
	if (args[cnt] == NULL)
		return (0);
	while (args[cnt] && unset_elem_check(args[cnt]))
	{
		in_unset(args[cnt]);
		cnt++;
	}
	return (0);
}