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
	return (size - 1);
}

void	sort_name(char **str, size_t size)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (str[i + 1])
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
	t_env	**tmp;
	size_t	cnt;
	char	*s;

	cnt = 0;
	while (str[cnt])
	{
		tmp = g_global.env;
		while (ft_strcmp(str[cnt], (*tmp)->name) != 0)
			tmp = &(*tmp)->next;
		s = "declare -x ";
		ft_putstr_fd(s, STDOUT_FILENO);
		ft_putstr_fd((*tmp)->name, STDOUT_FILENO);
		if ((*tmp)->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd((*tmp)->value, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		cnt++;
	}
	return (0);
}

void	put_export(t_env **tmp, size_t size)
{
	char	**str;
	size_t	cnt;

	str = (char **)malloc_error(sizeof(char *) * size);
	cnt = 0;
	while (*tmp)
	{
		str[cnt++] = (*tmp)->name;
		tmp = &(*tmp)->next;
	}
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

void	add_env(t_token **p_tok)
{
	char	*str;
	t_env	*new_env;
	t_env	*tmp;
	size_t	cnt;

	tmp = *g_global.env;
	if (!ft_isalpha((*p_tok)->next->word[0]) && (*p_tok)->next->word[0] != '_')
		return ;
	str = ft_strdup((*p_tok)->next->word);
	cnt = 0;
	while (str[cnt])
	{
		if (str[cnt] == '=')
			break ;
		cnt++;
	}
	// split_env = ft_split(str, '=');
	// if (split_env[2] || split_env == NULL)
	// 	exit(EXIT_FAILURE);
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
	if (tmp->next == NULL || operater_cmp(tmp->next->word, 0) != 0)
		put_export(env_tmp, size);
	while (tmp->next && tmp->next->kind == WORD)
	{
		add_env(&tmp);
		tmp = tmp->next;
		if (tmp->next && !ft_isalpha(tmp->next->word[0]) && tmp->next->word[0] != '_')
		{
			ft_putstr_fd("export: `", STDOUT_FILENO);
			ft_putstr_fd(tmp->next->word, STDOUT_FILENO);
			ft_putendl_fd("': not a valid identifier", STDOUT_FILENO);
		}
	}
	return (0);
}
