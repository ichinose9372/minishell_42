#include "minishell.h"

int	acces_check_file(char *argv)
{
	if (access(argv, F_OK) != 0)
		return (0);
	if (access(argv, X_OK) != 0)
		return (1);
	else
		return (0);
}

int	file_open_rd(char	*argv)
{
	int	fd;

	argv = create_absolute_path(argv);
	if (acces_check_file(argv))
		return (-1);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free(argv);
		perror("error");
		g_global.status = 1;
		return (-1);
	}
	free(argv);
	return (fd);
}

int	file_open_wrt(char	*argv)
{
	int	fd;

	argv = create_absolute_path(argv);
	if (acces_check_file(argv))
		return (-1);
	fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		free(argv);
		perror("error");
		g_global.status = 1;
		return (-1);
	}
	free(argv);
	return (fd);
}

int	file_open_wrt_add(char	*argv)
{
	int	fd;

	argv = create_absolute_path(argv);
	if (acces_check_file(argv))
		return (-1);
	fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		free(argv);
		perror("error");
		g_global.status = 1;
		return (-1);
	}
	free(argv);
	return (fd);
}