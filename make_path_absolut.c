#include "minishell.h"

char *create_absolute_path(char	*argv)
{
	char	*tmp;
	char	*tmp2;
	char	path_name[PATH_SIZE];

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
			tmp = ft_strtrim(argv, "~");	 
			tmp2 = new_getenv("HOME");
			argv = ft_strjoin(tmp2, tmp);
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
