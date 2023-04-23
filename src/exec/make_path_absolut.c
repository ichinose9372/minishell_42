#include "minishell.h"

char	*in_create_absolute_path(char *path_name, char	*argv)
{
	char	*tmp;
	// char	*tmp2;

	if (argv[1] == '.')
	{
		tmp = ft_strtrim(path_name, "/");
		ft_memset(path_name, 0, ft_strlen(path_name));
		ft_strlcpy(path_name, tmp, ft_strlen(tmp));
		free(tmp);
	}
	else if (argv[1] == '/')
	{
		// tmp = ft_strtrim(argv, ".");
		// tmp2 = new_getenv("PWD");
		// argv = ft_strjoin(tmp2, tmp);
		tmp = argv;
		argv = ft_strjoin(path_name, &argv[1]);
		// free(tmp);
		// free(tmp2);
	}
	else
		return (NULL);
	return (argv);
}

char	*create_absolute_path(char	*argv)
{
	char	*tmp;
	char	*tmp2;
	char	path_name[PATH_SIZE];

	if (!my_getcwd(path_name, PATH_SIZE))
		return (NULL);
	if (argv[0] == '.')
	{
		tmp = in_create_absolute_path(path_name, argv);
		return (tmp);
	}
	else if (argv[0] == '~' && argv[1] == '/')
	{
		tmp = ft_strtrim(argv, "~");
		tmp2 = new_getenv("HOME");
		argv = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		return (argv);
	}
	tmp = ft_strjoin("/", argv);
	argv = ft_strjoin(path_name, tmp);
	free(tmp);
	return (argv);
}
