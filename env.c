#include "minishell.h"

t_env	*new_env(char *str)
{
	t_env	*env;
	size_t	cnt;
	size_t	tmp;

	cnt = 0;
	env = (t_env *)malloc(sizeof(t_env));
	while (str[cnt] != '=')
		cnt++;
	env->name = new_strdup(str, cnt);
	cnt++;
	tmp = cnt;
	while (str[cnt])
		cnt++;
	env->value = new_strdup(&str[tmp], cnt - tmp);
	return (env);
}

t_env	*make_env()
{
	t_env	*env;
	t_env	*tmp;
	extern char	**environ;
	size_t	cnt;

	cnt = 0;
	env = new_env(environ[cnt++]);
	tmp = env;
	while (environ[cnt])
	{
		env->next = new_env(environ[cnt++]);
		env = env->next;
	}
	env = NULL;
	return (tmp);
}
