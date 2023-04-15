#include "minishell.h"

int	ft_isspace(char c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

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
	{
		if (nptr[cnt] == '-')
			type *= -1;
		cnt++;
	}
	while ('0' <= nptr[cnt] && nptr[cnt] <= '9')
	{
		number *= 10;
		number += nptr[cnt++] - '0';
		if (check_llong(number, nptr[cnt], type))
		{
			ft_putstr_fd("exit: ", STDOUT_FILENO);
			ft_putstr_fd(nptr, STDOUT_FILENO);
			ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
			exit (255);
		}
	}
	return (number * type);
}

int	check_digit(char *str)
{
	char	*tmp;

	tmp = str;
	if (*tmp == '-')
		tmp++;
	while (*tmp)
	{
		if (!ft_isdigit((int)*tmp))
			return (0);
		tmp++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	long long	status;
	size_t		cnt;

	cnt = 1;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args[cnt] == NULL)
		exit (g_global.status);
	if (args[cnt + 1])
	{
		ft_putendl_fd("exit: too many arguments", STDOUT_FILENO);
		g_global.status = 1;
		return (0);
	}
	if (check_digit(args[cnt]))
	{
		status = exit_atoi(args[cnt]);
		if (status < 256)
			exit (status);
		else if (status > 255)
		{
			status = status - 256 * (status / 256);
			exit (status);
		}
	}
	else
	{
		ft_putstr_fd("exit: ", STDOUT_FILENO);
		ft_putstr_fd(args[cnt], STDOUT_FILENO);
		ft_putendl_fd(" numeric argument required", STDOUT_FILENO);
	}
	exit(255);
}
