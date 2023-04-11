#include "minishell.h"

int	file_open_rd(char	*argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		g_global.status = 1;
	}
	return (fd);
}

int	file_open_wrt(char	*argv)
{
	int	fd;

	fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("Error");
		g_global.status = 1;
		return (0);
	}
	return (fd);
}

int	file_open_wrt_add(char	*argv)
{
	int	fd;

	fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		perror("Error");
		g_global.status = 1;
		return (0);
	}
	return (fd);
}
