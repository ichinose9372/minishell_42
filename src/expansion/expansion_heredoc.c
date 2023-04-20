#include "minishell.h"

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
			cnt += variable_expansion(&new_str, &str[cnt]);
		else
			cnt += char_expansion(&new_str, &str[cnt]);
	}
	free(str);
	if (!new_str)
		new_str = ft_calloc(1, 1);
	*top_str = new_str;
}
