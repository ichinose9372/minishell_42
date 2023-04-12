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
	if (LLONG_MAX / 10 < num && c && !minus)
		return (1);
	if (LLONG_MAX / 10 == num && LLONG_MAX % 10 <= c - '0' && !minus)
		return (1);
	if (LLONG_MIN / 10 > -num && c && minus)
		return (-1);
	if (LLONG_MIN / 10 == -num && LLONG_MIN % 10  > -(c - '0') && minus)
		return (-1);
	return (0);
}

long	exit_atoi(char *nptr)
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

int		check_digit(char *str)
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

int	builtin_exit(t_token **p_tok)
{
	long long	status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if ((*p_tok)->next == 0)
		exit (g_global.status);
	if ((*p_tok)->next->next)
	{
		if ((*p_tok)->next->next->kind == 0)
		{
			ft_putendl_fd("exit: too many arguments", STDOUT_FILENO);
			g_global.status = 1;
		}
		return (0);
	}
	if (check_digit((*p_tok)->next->word))
	{
		status = exit_atoi((*p_tok)->next->word);
		if (status < 256)
			exit (status);
		else if (status > 255)
		{
			status = status - 256 * (status / 256);
			printf("[%lld]\n", status);
			exit (status);
		}
	}
	else
	{
		ft_putstr_fd("exit: ", STDOUT_FILENO);
		ft_putstr_fd((*p_tok)->next->word, STDOUT_FILENO);
		ft_putendl_fd(" numeric argument required", STDOUT_FILENO);
	}
	exit(255);
}
