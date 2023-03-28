#include "minishell.h"

t_env	*new_env(char *str)
{
	t_env	*node;
	size_t	cnt;
	size_t	tmp;

	cnt = 0;
	node = (t_env *)malloc(sizeof(t_env));
	while (str[cnt] != '=')
		cnt++;
	node->name = new_strdup(str, cnt);
	cnt++;
	tmp = cnt;
	while (str[cnt])
		cnt++;
	node->value = new_strdup(&str[tmp], cnt - tmp);
	return (node);
}

void	make_env(void)
{
	t_env	*tmp;
	extern char	**environ;
	size_t	cnt;

	cnt = 0;
	env = (t_env **)malloc(sizeof(t_env *));
	tmp = new_env(environ[cnt++]);
	*env = tmp;
	while (environ[cnt])
	{
		tmp->next = new_env(environ[cnt++]);
		tmp = tmp->next;
	}
	tmp = NULL;
}
