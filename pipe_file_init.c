#include "minishell.h"

int acces_check_file(char *argv)
{
	if (access(argv, F_OK) != 0)
	{
		perror("open");
	}
	if (access(argv, R_OK) != 0)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

int	file_open_rd(char	*argv)
{
	int	fd;

	if (!acces_check_file(argv))
		return (-1);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		g_global.status = 1;
		return (-1);
	}
	return (fd);
}

int	file_open_wrt(char	*argv)
{
	int	fd;

	if (!acces_check_file(argv))
		return (-1);
	fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error");
		g_global.status = 1;
		return (-1);
	}
	return (fd);
}

int	file_open_wrt_add(char	*argv)
{
	int	fd;

	if (!acces_check_file(argv))
		return (-1);
	fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Error");
		g_global.status = 1;
		return (-1);
	}
	return (fd);
}
