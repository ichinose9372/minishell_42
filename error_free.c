#include "minishell.h"

void	command_not_found(char *str)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(str + 1, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd("command not found", 1);
	g_global.status = 127;
}

void	all_free(char **env_split)
{
	int	i;

	i = 0;
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
		free(tok->word);
		free(tok);
		tok = tok->next;
	}
}

void	all_free_and_tmp(char *tmp, char **env_split)
{
	all_free(env_split);
	free(tmp);
}


