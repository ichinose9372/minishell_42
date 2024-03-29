/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:16 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/26 14:48:17 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	option_check(char *str)
{
	int	cnt;

	cnt = 1;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[cnt])
		{
			if (str[cnt] != 'n')
				return (0);
			cnt++;
		}
		return (1);
	}
	return (0);
}

void	put_args(char	**args, int cnt)
{
	while (args[cnt])
	{
		ft_putstr_fd(args[cnt], STDOUT_FILENO);
		cnt++;
		if (args[cnt])
			ft_putchar_fd(' ', 1);
	}
}

int	builtin_echo(char **args)
{
	int		flag;
	size_t	cnt;

	cnt = 0;
	if (args[cnt++] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	flag = 0;
	while (args[cnt] && option_check(args[cnt]))
	{
		flag = 1;
		cnt++;
	}
	put_args(args, cnt);
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	g_global.status = 0;
	return (0);
}
