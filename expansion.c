#include "minishell.h"

char	*new_strjoin(char const *s1, char const *s2, size_t s2_len)
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
	str = (char *)malloc(len + 1);
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

	tmp = *env;
	len = ft_strlen(name);
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, len + 1))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

size_t	variable_expansion(char **dest, char *src)
{
	size_t	cnt;
	char	*tmp;
	char	*name;

	cnt = 1;
	if (src[cnt] == '\0' || src[cnt] == '\"' || src[cnt] == '\"')
	{
		tmp = new_strjoin(*dest, src, 1);
		free(*dest);
		*dest = tmp;
		return (cnt);
	}
	if (!check_variable(src, &cnt))
		return (cnt + 1);
	name = new_strdup(&src[1], cnt - 1);
	tmp = ft_strjoin(*dest, new_getenv(name));
	free(*dest);
	*dest = tmp;
	return (cnt);
}

size_t	double_expansion(char **dest, char *src)
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

size_t	single_expansion(char **dest, char *src)
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


size_t	char_expansion(char **dest, char *src)
{
	char	*tmp;

	tmp = new_strjoin(*dest, src, 1);
	free(*dest);
	*dest = tmp;
	return (1);
}

void	expansion(t_token *tok, t_token **p_tok)
{
	char	*new_word;
	size_t	cnt;

	*p_tok = tok;
	while (tok)
	{
		new_word = NULL;
		cnt = 0;
		while (tok->word[cnt])
		{
			if (tok->word[cnt] == '\"')
				cnt += double_expansion(&new_word, &tok->word[cnt + 1]);
			else if (tok->word[cnt] == '\'')
				cnt += single_expansion(&new_word, &tok->word[cnt + 1]);
			else if (tok->word[cnt] == '$')
				cnt += variable_expansion(&new_word, &tok->word[cnt]);
			else
				cnt += char_expansion(&new_word, &tok->word[cnt]);
		}
		free(tok->word);
		if (!new_word)
			new_word = ft_calloc(1, 1);
		tok->word = new_word;
		tok = tok->next;
	}\
}