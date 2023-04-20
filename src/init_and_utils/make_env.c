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

int	count_environ(t_env	*env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

char	*in_convet_func(t_env *env)
{
	char	*tmp;
	char	*mini_environ;

	mini_environ = ft_strdup(env->name);
	tmp = ft_strjoin(mini_environ, "=");
	if (!tmp)
		exit(1);
	free(mini_environ);
	mini_environ = tmp;
	tmp = ft_strjoin(mini_environ, env->value);
	if (!tmp)
		exit(1);
	free(mini_environ);
	mini_environ = tmp;
	return (mini_environ);
}

char	**convet_environ(void)
{
	int		cnt;
	t_env	*env;
	char	**mini_environ;

	env = *g_global.env;
	cnt = count_environ(env);
	mini_environ = (char **)malloc(sizeof(char *) * cnt + 1);
	if (!mini_environ)
		exit(1);
	env = *g_global.env;
	cnt = 0;
	while (env)
	{
		if (env->value)
		{
			mini_environ[cnt] = in_convet_func(env);
			cnt++;
		}
		env = env->next;
	}
	mini_environ[cnt] = NULL;
	return (mini_environ);
}
