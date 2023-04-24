#include "minishell.h"

size_t	count_env(t_env *tmp)
{
	int	size;

	size = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
			size--;
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

	tmp = *g_global.env;
	cnt = 0;
	while (str[cnt])
	{
		if (ft_strcmp(str[cnt], "OLDPWD") == 0)
		{
			put_export_environ(tmp, str[cnt]);
			ft_putchar_fd('\n', STDOUT_FILENO);
			cnt++;
		}
		else
		{
			tmp = *g_global.env;
			while (ft_strcmp(str[cnt], tmp->name) != 0)
				tmp = tmp->next;
			put_export_environ(tmp, str[cnt]);
			cnt++;
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	return (0);
}

void	put_export(size_t size)
{
	char	**str;
	size_t	cnt;
	t_env	*tmp;
	int		i;

	tmp = *g_global.env;
	if (g_global.oldpwd == NULL)
		size += 1;
	str = (char **)malloc_error(sizeof(char *) * size + 1);
	cnt = 0;
	while (tmp)
	{
		str[cnt] = tmp->name;
		tmp = tmp->next;
		cnt++;
	}
	str[cnt] = ft_strdup("OLDPWD");
	cnt++;
	str[cnt] = NULL;
	sort_name(str, size);
	i = 0;
	while (str[i])
	{
		printf("str[] = %s\n", str[i]);
		i++;
	}
	print_export(str);
	free(str);
	g_global.status = 0;
}

int	builtin_export(char **args)
{
	t_env	*env_tmp;
	size_t	size;
	size_t	cnt;
	int		status;

	status = 0;
	env_tmp = *g_global.env;
	cnt = 1;
	size = count_env(env_tmp);
	if (args[cnt] == NULL)
		put_export(size);
	while (args[cnt])
	{
		if (add_env(args[cnt++]) == 1)
			status = 1;
	}
	return (status);
}
