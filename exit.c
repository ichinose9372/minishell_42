#include "minishell.h"

int		check_digit(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (!(ft_isdigit((int)*tmp)))
			return (0);
		tmp++;
	}
	return (1);
}

int	builtin_exit(t_token **p_tok)
{
	int		status;

	if ((*p_tok)->next == 0)
		exit (1);
	if ((*p_tok)->next->next != NULL)
	{
		perror("exit");
		return (1);
	}
	if (check_digit((*p_tok)->next->word))
	{
		status = ft_atoi((*p_tok)->next->word);
		exit (status);
	}
	exit(255);
}
