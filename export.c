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

bool	put_export(t_env **tmp, size_t size)
{
	char	**str;
	size_t	cnt;

	str = (char **)malloc(sizeof(char *) * size);
	if (!str)
		return (false);
	cnt = 0;
	while (*tmp)
	{
		str[cnt++] = (*tmp)->name;
		tmp = &(*tmp)->next;
	}
	sort_name(str, size);
	print_export(str);
	return (true);
}

void	add_env(t_token **p_tok)
{
	char	*str;
	char	**split_env;
	t_env	*new_env;
	t_env	*tmp;

	tmp = *g_global.env;
	str = ft_strdup((*p_tok)->next->word);
	split_env = ft_split(str, '=');
	if (split_env[2] || split_env == NULL)
		exit(EXIT_FAILURE);
	new_env = malloc(sizeof(t_env));
	if (new_env == NULL)
		exit(EXIT_FAILURE);
	new_env->next = NULL;
	new_env->name = ft_strdup(split_env[0]);
	new_env->value = ft_strdup(split_env[1]);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_env;
}

int	builtin_export(t_token **p_tok)
{
	t_env	**tmp;
	size_t	size;

	tmp = g_global.env;
	size = count_env(tmp);
	if ((*p_tok)->next == NULL || operater_cmp((*p_tok)->next->word, 0) != 0)
		put_export(tmp, size);
	else if ((*p_tok)->next->word && (*p_tok)->next->next == NULL)
		add_env(p_tok);
	else
		printf("error\n");
	return (0);
}
