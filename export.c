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

// void	sort_name(char **str, size_t size)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*tmp;

// 	i = 0;
// 	while(i < size - 1)
// 	{
// 		j = 0;
// 		while (j - 1 < size - 1)
// 		{
// 			// printf("i = %zu j = %zu\n", i, j);
// 			if (ft_strcmp(str[j], str[j + 1]) > 0)
// 			{
// 				// printf("%s %s\n", str[j], str[j + 1]);
// 				tmp = str[j];
// 				str[j] = str[j + 1];
// 				str[j + 1] = tmp;
// 				// printf("%s %s\n", str[j], str[j + 1]);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// bool	put_export(t_env *tmp, size_t size)
// {
// 	char	**str;
// 	size_t	cnt;

// 	str = (char **)malloc(sizeof(char *) * size);
// 	if (!str)
// 		return (false);
// 	cnt = 0;
// 	while (tmp)
// 	{
// 		str[cnt++] = tmp->name;
// 		tmp = tmp->next;
// 	}
// 	// printf("%s\n", str[0]);
// 	sort_name(str, size);
// 	// printf("%s\n", str[0]);
// 	int i = 0;
// 	while (str[i])
// 	{
// 		printf("%s\n", str[i++]);

// 	}
// 	return (true);
// }

int	put_export(t_env **tmp, size_t size)
{
	size_t	i;
	size_t	j;
	char	*s1;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i)
		{
			if (ft_strcmp((*tmp)->name, (*tmp)->next->name) > 0)
			{
				s1 = (*tmp)->name;
				(*tmp)->name = (*tmp)->next->name;
				(*tmp)->next->name = s1;
			}
			*tmp = (*tmp)->next;
			j++;
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_token **p_tok)
{
	t_env	**tmp;
	size_t	size;

	tmp = env;
	size = count_env(*tmp);
	printf("size = %zu\n", size);
	if ((*p_tok)->next == NULL || operater_cmp((*p_tok)->next->word, 0) != 0)
		put_export(tmp, size);
	while (tmp)
	{
		printf("%s\n", (*tmp)->name);
		*tmp = (*tmp)->next;
	}
	return (0);
}