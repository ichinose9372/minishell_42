#include "minishell.h"

size_t	count_env(t_env *tmp)
{
	int	size;

	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
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
	g_global.status = 0;
}

int	builtin_export(char **args)
{
	t_env	*env_tmp;
	size_t	size;
	size_t	cnt;

	env_tmp = *g_global.env;
	cnt = 1;
	size = count_env(env_tmp);
	if (args[cnt] == NULL)
		put_export(size);
	while (args[cnt])
		add_env(args[cnt++]);
	return (0);
}
