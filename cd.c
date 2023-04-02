#include "minishell.h"

char	*my_getcwd(char *buf, size_t length)
{
	size_t	size;
	t_env	**tmp;

	tmp = global.env;
	while (ft_strncmp((*tmp)->name, "PWD", 4) != 0)
		tmp = &(*tmp)->next;
	size = 0;
	while (size < length - 1 && (*tmp)->value[size])
	{
		buf[size] = (*tmp)->value[size];
		size++;
	}
	buf[size] = '\0';
	return (buf);
}

void	remake_pwd(char	*new_path)
{
	t_env	**tmp;
	size_t	size;

	tmp = global.env;
	while (ft_strncmp((*tmp)->name, "PWD", 4) != 0)
		tmp = &(*tmp)->next;
	size = 0;
	while (new_path[size])
	{
		(*tmp)->value[size] = new_path[size];
		size++;
	}
	(*tmp)->value[size] = '\0';
}

char	*prev_move(char	*path_name)
{
	char	*last;
	char	*new_path;
	size_t	len;
	int		ret;

	last = ft_strrchr(path_name, '/');
	len = ft_strlen(path_name) - ft_strlen(last);
	new_path = ft_substr(path_name, 0, len);
	ret = chdir(new_path);
	if (ret == -1)
	{
		perror("chdir");
		exit(1);
	}
	return (new_path);
}

char	*next_move(char	*path_name, char *word)
{
	char	*tmp;
	int		ret;
	char	*new_path;

	tmp = ft_strjoin("/", word);
	printf("tmp = %s\n", tmp);
	new_path = ft_strjoin(path_name, tmp);
	printf("new_path = %s\n", new_path);
	ret = chdir(new_path);
	if (ret == -1)
	{
		perror("chdir");
		exit(1);
	}
	free(tmp);
	return (new_path);


}
int	builtin_cd(t_token **p_tok)
{
	char	path_name[PATH_SIZE];
	char	*new_path;

	if (!my_getcwd(path_name, PATH_SIZE))
		return (1);
	if (ft_strncmp((*p_tok)->next->word, "..", 3) == 0)
	{
		new_path = prev_move(path_name);
		remake_pwd(new_path);
		free(new_path);
	}
	else if ((*p_tok)->next->word)
	{
		new_path = next_move(path_name, (*p_tok)->next->word);
		remake_pwd(new_path);
		free(new_path);
	}
	return (0);
}
