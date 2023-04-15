#include "minishell.h"

char	*h_new_strjoin(char const *s1, char const *s2, size_t s2_len)
{
	size_t	len;
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (new_strdup(s2, s2_len));
	if (!s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + s2_len;
	str = (char *)malloc_error(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}

bool	h_check_variable(char *src, size_t *cnt)
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

char	*h_new_getenv(char *name)
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

size_t	h_variable_expansion(char **dest, char *src)
{
	size_t	cnt;
	char	*tmp;
	char	*name;

	cnt = 1;
	if (src[cnt] == '\0' || src[cnt] == ' ')
	{
		tmp = new_strjoin(*dest, src, 1);
		free(*dest);
		*dest = tmp;
		return (cnt);
	}
	else if (src[cnt] == '?')
	{
		*dest = ft_itoa(g_global.status);
		return (cnt + 1);
	}
	if (!check_variable(src, &cnt))
		return (cnt + 1);
	name = new_strdup(&src[1], cnt - 1);
	tmp = ft_strjoin(*dest, new_getenv(name));
	free(name);
	free(*dest);
	*dest = tmp;
	return (cnt);
}

size_t	h_double_expansion(char **dest, char *src)
{
	size_t	cnt;
	size_t	last_cnt;
	char	*tmp;

	cnt = 0;
	last_cnt = 0;
	while (src[cnt] != '\"')
	{
		if (src[cnt] == '$')
		{
			tmp = new_strjoin(*dest, src, cnt - last_cnt);
			free(*dest);
			*dest = tmp;
			cnt += variable_expansion(dest, &src[cnt]);
			last_cnt = cnt;
		}
		else
			cnt++;
	}
	tmp = new_strjoin(*dest, &src[last_cnt], cnt - last_cnt);
	free(*dest);
	*dest = tmp;
	return (cnt + 2);
}

size_t	h_single_expansion(char **dest, char *src)
{
	size_t	cnt;
	char	*tmp;

	cnt = 0;
	while (src[cnt] != '\'')
		cnt++;
	tmp = new_strjoin(*dest, src, cnt);
	free(*dest);
	*dest = tmp;
	return (cnt + 2);
}

size_t	h_char_expansion(char **dest, char *src)
{
	char	*tmp;

	tmp = new_strjoin(*dest, src, 1);
	free(*dest);
	*dest = tmp;
	return (1);
}

void	expansion_heredoc(char **top_str)
{
	char	*new_str;
	char	*str;
	size_t	cnt;

	str = *top_str;
	cnt = 0;
	new_str = NULL;
	while (str[cnt])
	{
		if (str[cnt] == '$')
			cnt += h_variable_expansion(&new_str, &str[cnt]);
		else
			cnt += h_char_expansion(&new_str, &str[cnt]);
	}
	free(str);
	if (!new_str)
		new_str = ft_calloc(1, 1);
	*top_str = new_str;
}
