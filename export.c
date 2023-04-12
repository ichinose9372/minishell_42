#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	count_env(t_env **tmp)
{
	int	size;

	size = 0;
	while (*tmp)
	{
		size++;
		tmp = &(*tmp)->next;
	}
	return (size);
}

void	sort_name(char **str, size_t size)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 1;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i)
		{
			if (ft_strcmp(str[j], str[j + 1]) > 0)
			{
				tmp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_export(char **str)
{
	t_env	*tmp;
	size_t	cnt;
	char	*s;

	cnt = 1;
	while (str[cnt])
	{
		tmp = *g_global.env;
		while (ft_strcmp(str[cnt], tmp->name) != 0)
			tmp = tmp->next;
		s = "declare -x ";
		ft_putstr_fd(s, STDOUT_FILENO);
		ft_putstr_fd(tmp->name, STDOUT_FILENO);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		cnt++;
	}
	return (0);
}

void	put_export(size_t size)
{
	char	**str;
	size_t	cnt;
	t_env	*tmp;

	tmp = *g_global.env;
	str = (char **)malloc_error(sizeof(char *) * size + 1);
	cnt = 0;
	while (tmp)
	{
		str[cnt] = tmp->name;
		tmp = tmp->next;
		cnt++;
	}
	str[cnt] = NULL;
	sort_name(str, size);
	print_export(str);
	free(str);
}

int	env_overwrite(char *str, size_t cnt)
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
	if (str[cnt] =='\0')
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(&str[cnt + 1]);
	return (1);
}

int	export_elem_check(char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt] && (str[cnt] != '=' && str[cnt] != '+'))
	{
		if ((cnt == 0 && !ft_isalpha(str[cnt]) && str[cnt] != '_') || \
			(cnt != 0 && !ft_isalnum(str[cnt]) && str[cnt] != '_'))
		{
			ft_putstr_fd("export: `", STDOUT_FILENO);
			ft_putstr_fd(str, STDOUT_FILENO);
			ft_putendl_fd("': not a valid identifier", STDOUT_FILENO);
			g_global.status = 1;
			return (1);
		}
		cnt++;
	}
	if (str[cnt] == '+' && str[cnt + 1] != '=')
	{
		ft_putstr_fd("export: `", STDOUT_FILENO);
		ft_putstr_fd(str, STDOUT_FILENO);
		ft_putendl_fd("': not a valid identifier", STDOUT_FILENO);
		g_global.status = 1;
		return (1);
	}
	return (0);
}

int	env_join(char *str, size_t cnt)
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

void	add_env(t_token **p_tok)
{
	char	*str;
	t_env	*new_env;
	t_env	*tmp;
	size_t	cnt;

	tmp = *g_global.env;
	if (export_elem_check((*p_tok)->next->word))
		return ;
	str = ft_strdup((*p_tok)->next->word);
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
			return ;
	}
	if (env_overwrite(str, cnt))
	{
		free(str);
		return ;
	}
	new_env = (t_env *)malloc_error(sizeof(t_env));
	new_env->name = new_strdup(str, cnt);
	if (str[cnt] == '=')
		new_env->value = new_strdup(&str[cnt + 1], ft_strlen(str) - cnt + 1);
	else if (str[cnt] == '\0')
		new_env->value = NULL;
	new_env->next = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_env;
	free(str);
}

int	builtin_export(t_token **p_tok)
{
	t_env	**env_tmp;
	size_t	size;
	t_token	*tmp;

	env_tmp = g_global.env;
	tmp = *p_tok;
	size = count_env(env_tmp);
	if ((tmp->next == NULL || operater_cmp(tmp->next->word, 0) != 0))
		put_export(size);
	while (tmp->next && tmp->next->kind == WORD)
	{
		add_env(&tmp);
		tmp = tmp->next;
	}
	return (0);
}
