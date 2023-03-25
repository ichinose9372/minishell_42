#include "minishell.h"

char	*new_strjoin(char const *s1, char const *s2, size_t s2_len)
{
	size_t	len;
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (new_strdup(s2, s2_len));
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

size_t	double_expansion(char **dest, char *src)
{
	size_t	cnt;
	size_t	last_cnt;
	char	*tmp;

	cnt = 0;
	last_cnt = 0;
	while (src[cnt] != '\"')
	{
		// if (src[cnt] == '$')
		// {
		// 	tmp = new_strjoin(*dest, src, cnt);
		// 	free(*dest);
		// 	*dest = tmp;
		// 	free(tmp);
		// 	cnt += variable_expantion(*dest, src);
		// 	last_cnt = cnt;
		// }
		cnt++;
	}
	tmp = new_strjoin(*dest, src, cnt - last_cnt);
	free(*dest);
	*dest = tmp;
	free(tmp);
	return (cnt + 1);
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
	free(tmp);
	return (cnt + 1);
}

size_t	char_expansion(char **dest, char *src)
{
	char	*tmp;

	tmp = new_strjoin(*dest, src, 1);
	printf("tmp = %s\n", tmp);
	free(*dest);
	*dest = tmp;
	free(tmp);
	return (1);
}

t_token	**expansion(t_token *tok)
{
	t_token	**p_tok;
	char	*new_word;
	size_t	cnt;

	p_tok = &tok;
	while (tok)
	{
		new_word = NULL;
		cnt = 0;
		while (tok->word[cnt])
		{
			// if (tok->word[cnt] == '\"')
			// 	cnt += double_expansion(&new_word, &tok->word[cnt + 1]);
			if (tok->word[cnt] == '\'')
				cnt += single_expansion(&new_word, &tok->word[cnt + 1]);
			else
				cnt += char_expansion(&new_word, &tok->word[cnt]);
		}
		free(tok->word);
		tok->word = new_word;
		tok = tok->next;
	}
	printf("test2\n");
	return (p_tok);
}