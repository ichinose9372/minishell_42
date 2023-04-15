#include "minishell.h"

t_env	*new_env(char *str)
{
	t_env	*node;
	size_t	cnt;
	size_t	tmp;

	cnt = 0;
	node = (t_env *)malloc_error(sizeof(t_env));
	while (str[cnt] != '=')
		cnt++;
	node->name = new_strdup(str, cnt);
	cnt++;
	tmp = cnt;
	while (str[cnt])
		cnt++;
	node->value = new_strdup(&str[tmp], cnt - tmp);
	node->next = NULL;
	return (node);
}

t_env	**make_env(void)
{
	t_env		*tmp;
	t_env		**ret;
	extern char	**environ;
	size_t		cnt;

	cnt = 0;
	ret = (t_env **)malloc_error(sizeof(t_env *));
	if (!*environ)
	{
		*ret = (t_env *)malloc_error(sizeof(t_env));
		(*ret)->name = ft_calloc(1, 1);
		(*ret)->value = NULL;
		(*ret)->next = NULL;
		return (ret);
	}
	tmp = new_env(environ[cnt++]);
	*ret = tmp;
	while (environ[cnt])
	{
		tmp->next = new_env(environ[cnt++]);
		tmp = tmp->next;
	}
	return (ret);
}
