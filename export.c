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

size_t	count_env(t_env *tmp)
{
	int	size;

	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size - 1);
}

void	sort_name(char **str, size_t size)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while(str[i + 1])
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
	char *s;

	cnt = 0;
	while (str[cnt])
	{
		tmp = *env;
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

bool	put_export(t_env *tmp, size_t size)
{
	char	**str;
	size_t	cnt;

	str = (char **)malloc(sizeof(char *) * size);
	if (!str)
		return (false);
	cnt = 0;
	while (tmp)
	{
		str[cnt++] = tmp->name;
		tmp = tmp->next;
	}
	sort_name(str, size);
	print_export(str);
	return (true);
}

// int	put_export(t_env **tmp, size_t size)
// {
// 	t_env	*tmp1;
// 	t_env	*tmp2;
// 	t_env	*tmptmp;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (i < size - 1)
// 	{
// 		tmp1 = *tmp;
// 		j = 0;
// 		while (j < size - i - 1)
// 		{
// 			tmp2 = tmp1->next;
// 			if (ft_strcmp(tmp1->name, tmp2->name) > 0)
// 			{
// 				tmptmp = tmp1->next;
// 				tmp1->next = tmp2->next;
// 				tmp2->next = tmptmp;
// 			}
// 			tmp1 = tmp1->next;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	builtin_export(t_token **p_tok)
{
	t_env	**tmp;
	size_t	size;
	// char	*str;

	tmp = env;
	size = count_env(*tmp);
	if ((*p_tok)->next == NULL || operater_cmp((*p_tok)->next->word, 0) != 0)
	{
		// while (*tmp)
		// {
		// 	printf("%s!!%s\n", (*tmp)->name, (*tmp)->value);
		// 	tmp = &(*tmp)->next;
		// }
		// printf("aaa\n");
		put_export(*tmp, size);
		// while (*tmp)
		// {
		// 	str = "declare -x ";
		// 	ft_putstr_fd(str, STDOUT_FILENO);
		// 	ft_putstr_fd((*tmp)->name, STDOUT_FILENO);
		// 	ft_putstr_fd("=\"", STDOUT_FILENO);
		// 	ft_putstr_fd((*tmp)->value, STDOUT_FILENO);
		// 	ft_putstr_fd("\"\n", STDOUT_FILENO);
		// 	*tmp = (*tmp)->next;
		// }
	}
	return (0);
}
