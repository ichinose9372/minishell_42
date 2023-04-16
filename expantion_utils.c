#include "minishell.h"

bool	check_variable(char *src, size_t *cnt)
{
	if (!ft_isalpha(src[*cnt]) && src[*cnt] != '_')
		return (false);
	*cnt += 1;
	while (src[*cnt])
	{
		if (!ft_isalnum(src[*cnt]) && src[*cnt] != '_')
			break ;
		*cnt += 1;
	}
	return (true);
}

char	*new_getenv(char *name)
{
	t_env	*tmp;
	size_t	len;

	tmp = *g_global.env;
	len = ft_strlen(name);
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, len + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*variable_join(char *src, char *dest, size_t cnt)
{
	char	*name;
	char	*tmp;

	name = new_strdup(&src[1], cnt - 1);
	tmp = ft_strjoin(dest, new_getenv(name));
	free(name);
	free(dest);
	return (tmp);
}

size_t	variable_expansion(char **dest, char *src)
{
	size_t	cnt;
	char	*tmp;

	cnt = 1;
	if (src[cnt] == '\0' || src[cnt] == '\'' || src[cnt] == '\"')
	{
		tmp = new_strjoin(*dest, src, 1);
		free(*dest);
		*dest = tmp;
		return (cnt);
	}
	else if (src[cnt] == '?')
	{
		tmp = ft_strjoin(*dest, ft_itoa(g_global.status));
		free(*dest);
		*dest = tmp;
		return (cnt + 1);
	}
	if (!check_variable(src, &cnt))
		return (cnt + 1);
	*dest = variable_join(src, *dest, cnt);
	return (cnt);
}