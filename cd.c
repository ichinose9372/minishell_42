#include "minishell.h"

int	builtin_cd(t_token **p_tok)
{
	char	path_name[PATH_SIZE];
	char	*new_path;
	char	*last;
	size_t	len;
	int		let;

	if (!getcwd(path_name, PATH_SIZE))
		return (1);
	if (ft_strncmp((*p_tok)->next->word, "..", 3) == 0)
	{
		last = ft_strrchr(path_name, '/');
		len = ft_strlen(path_name) - ft_strlen(last);
		new_path = ft_substr(path_name, 0, len);
		let = chdir(new_path);
		if (let == -1)
		{
			perror("chdir");
			exit(1);
		}
		free(new_path);
	}
	else if ((*p_tok)->next->word)
	{
		let = chdir((*p_tok)->next->word);
		if (let == -1)
		{
			perror("chdir");
			exit(1);
		}
	}
	else
	{
		while (*environ)
		{
			if ((ft_strncmp(*environ, "HOME=", 5)) == 0)
				break ;
			environ++;
		}
		new_path = ft_strtrim(*environ, "HOME=");
		let = chdir(new_path);
		if (let == -1)
		{
			perror("chdir");
			exit(1);
		}
	}
	return (0);
}
