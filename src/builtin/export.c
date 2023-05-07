/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:51 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/07 20:00:35 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	cnt = 0;
	while (str[cnt])
	{
		if (cnt == 0 && str[0][0] == '\0')
			cnt++;
		if (!str[cnt])
			break ;
		tmp = *g_global.env;
		while (ft_strcmp(str[cnt], tmp->name) != 0)
			tmp = tmp->next;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
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
	str = (char **)malloc_error(sizeof(char *) * (size + 1));
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
