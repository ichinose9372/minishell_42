#include "minishell.h"

static int	env_overwrite(char *str, size_t cnt)
{
	t_env	*tmp;

	tmp = *g_global.env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, str, cnt) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL || (tmp->name[cnt] != '=' && tmp->name[cnt] != '\0'))
		return (0);
	if (str[cnt] == '\0')
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(&str[cnt + 1]);
	return (1);
}

static int	export_elem_check(char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt])
	{
		if ((cnt == 0 && !ft_isalpha(str[cnt]) && str[cnt] != '_') || \
			(cnt != 0 && !ft_isalnum(str[cnt]) && str[cnt] != '_'))
			return (export_elem_error(str));
		cnt++;
		if (str[cnt] == '=' || str[cnt] == '+')
			break ;
	}
	if (str[cnt] == '+' && str[cnt + 1] != '=')
		return (export_elem_error(str));
	return (0);
}

static int	env_join(char *str, size_t cnt)
{
	t_env	*env;
	char	*tmp;

	env = *g_global.env;
	while (env)
	{
		if (ft_strncmp(env->name, str, cnt - 1) == 0)
			break ;
		env = env->next;
	}
	if (!env || (env->name[cnt] != '=' && env->name[cnt] != '\0'))
		return (0);
	tmp = ft_strjoin(env->value, &str[cnt + 1]);
	free(env->value);
	env->value = tmp;
	return (1);
}

static size_t	set_cnt(char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt])
	{
		if (str[cnt] == '=')
			break ;
		cnt++;
	}
	if (str[cnt - 1] == '+')
	{
		if (env_join(str, cnt))
			return (0);
	}
	if (env_overwrite(str, cnt))
		return (0);
	return (cnt);
}

void	add_env(char *str)
{
	t_env	*new_env;
	t_env	*tmp;
	size_t	cnt;

	if (export_elem_check(str))
		return ;
	cnt = set_cnt(str);
	if (cnt == 0)
		return ;
	new_env = (t_env *)malloc_error(sizeof(t_env));
	new_env->name = new_strdup(str, cnt);
	if (str[cnt] == '=')
		new_env->value = new_strdup(&str[cnt + 1], ft_strlen(str) - cnt + 1);
	else if (str[cnt] == '\0')
		new_env->value = NULL;
	new_env->next = NULL;
	tmp = *g_global.env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_env;
	g_global.status = 0;
}
