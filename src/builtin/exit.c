/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:23 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/04 14:15:41 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_llong(long num, char c, int minus)
{
	if (LLONG_MAX / 10 < num && c && minus == 1)
		return (1);
	if (LLONG_MAX / 10 == num && LLONG_MAX % 10 < c - '0' && minus == 1)
		return (1);
	if (LLONG_MIN / 10 > -num && c && minus == -1)
		return (1);
	if (LLONG_MIN / 10 == -num && LLONG_MIN % 10 > -(c - '0') && minus == -1)
		return (1);
	return (0);
}

long long	exit_atoi(char *nptr)
{
	int			type;
	long long	number;
	size_t		cnt;

	type = 1;
	number = 0;
	cnt = 0;
	while ((nptr[cnt] >= '\t' && nptr[cnt] == '\r') || nptr[cnt] == ' ')
		cnt++;
	if (nptr[cnt] == '+' || nptr[cnt] == '-')
		type = 1 - 2 * (nptr[cnt++] == '-');
	while ('0' <= nptr[cnt] && nptr[cnt] <= '9')
	{
		number = number * 10 + (nptr[cnt++] - '0');
		if (check_llong(number, nptr[cnt], type))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(nptr, STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit (255);
		}
	}
	return (number * type);
}

int	check_digit(char *str)
{
	char	*tmp;

	tmp = str;
	if (*tmp == '-' || *tmp == '+')
		tmp++;
	while (*tmp)
	{
		if (!ft_isdigit((int)*tmp))
			return (0);
		tmp++;
	}
	return (1);
}

int	set_exit(char *str)
{
	int	status;

	if (check_digit(str))
	{
		status = exit_atoi(str);
		if (status < 256)
			return (status);
		else if (status > 255)
		{
			status = status - 256 * (status / 256);
			return (status);
		}
	}
	else
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	builtin_exit(char **args)
{
	size_t		cnt;
	int			status;

	cnt = 1;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args[cnt] == NULL)
		exit (g_global.status);
	if (args[cnt][0] == '\0')
	{
		ft_putendl_fd("exit: : numeric argument required", STDERR_FILENO);
		exit (255);
	}
	status = set_exit(args[cnt]);
	if (status == -1)
		exit(255);
	else if (args[cnt + 1])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit (status);
	return (1);
}
