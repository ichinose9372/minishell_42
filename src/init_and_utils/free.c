#include "minishell.h"

void	all_free(char **env_split)
{
	int	i;

	i = 0;
	if (!env_split)
		return ;
	if (env_split[i] == NULL)
		i++;
	while (env_split[i])
	{
		free(env_split[i]);
		i++;
	}
	free(env_split);
}

void	path_all_free(char **env_split)
{
	int	i;

	i = 1;
	while (env_split[i])
	{
		free(env_split[i]);
		i++;
	}
	free(env_split);
}

void	all_free_token(t_token **p_tok)
{
	t_token	*tmp;

	while (*p_tok)
	{
		tmp = (*p_tok)->next;
		free((*p_tok)->word);
		free((*p_tok)->old_word);
		free(*p_tok);
		*p_tok = tmp;
	}
	free(p_tok);
	p_tok = NULL;
}

void	free_token(t_token *tok)
{
	while (tok)
	{
		if (tok->word)
			free(tok->word);
		if (tok->old_word)
			free(tok->old_word);
		free(tok);
		tok = tok->next;
	}
}

void	all_free_and_tmp(char *tmp, char **env_split)
{
	all_free(env_split);
	free(tmp);
}
