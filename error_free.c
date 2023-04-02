#include "minishell.h"

void	command_not_found(char *str)
{
	ft_putstr_fd("command not found: ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
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

void	all_free_and_tmp(char *tmp, char **env_split)
{
	all_free(env_split);
	free(tmp);
}
