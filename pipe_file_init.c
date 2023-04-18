#include "minishell.h"

char *create_absolute_path(char	*argv)
{
	char	*tmp;
	char	*tmp2;
	char	path_name[PATH_SIZE];

	if (argv[0] == '~' && argv[1] == '/')
		return (argv);
	if (!my_getcwd(path_name, PATH_SIZE))
		return (NULL);
	while (1)
	{
		if (argv[0] == '.' && argv[1] == '.')
		{
			tmp = ft_strtrim(path_name, "/");
			ft_memset(path_name, 0, ft_strlen(path_name));
			ft_strlcpy(path_name, tmp, ft_strlen(tmp));
		}
		else if (argv[0] == '.' && argv[1] == '/')
		{
			tmp = argv;
			argv = ft_strtrim(tmp, "/");
			free(tmp);
		}
		else if (argv[0] == '~' && argv[1] == '/')
		{
			tmp = argv;
			argv = ft_strtrim(tmp, "/");
			tmp2 = getenv("HOME");
			free(tmp);
			tmp = ft_strjoin(tmp2, argv);
			free(argv);
			argv = tmp;
			return (argv);
		}
		else
			break ;

	}
	tmp = ft_strjoin("/", argv);
	free(argv);
	argv = ft_strjoin(path_name, tmp);
	free(tmp);
	return (argv);
}

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
		g_global.status = 1;
		return (-1);
	}
	return (fd);
}

int	file_open_wrt(char	*argv)
{
	int	fd;

	if (acces_check_file(argv))
		return (-1);
	fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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

	if (acces_check_file(argv))
		return (-1);
	fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror("Error");
		g_global.status = 1;
		return (-1);
	}
	return (fd);
}
