#include "minishell.h"

int	option_check(t_token *tmp)
{
	int	cnt;

	cnt = 1;
	if (ft_strncmp(tmp->word, "-n", 2) == 0)
	{
		while (tmp->word[cnt])
		{
			if (tmp->word[cnt] != 'n')
				return (0);
			cnt++;
		}
		return (1);
	}
	return (0);
}

int	builtin_echo(t_token **p_tok)
{
	t_token	*tmp;
	int		flag;

	if ((*p_tok)->next == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	tmp = (*p_tok)->next;
	flag = 0;
	while (option_check(tmp))
	{
		flag = 1;
		tmp = tmp->next;
	}
	while (tmp && operater_cmp(tmp->word, 0) == 0)
	{
		ft_putstr_fd(tmp->word, 1);
		tmp = tmp->next;
		if (tmp && operater_cmp(tmp->word, 0) == 0)
			ft_putchar_fd(' ', 1);
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
