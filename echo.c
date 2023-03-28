#include "minishell.h"

int	builtin_echo(t_token **p_tok)
{
	t_token	*tmp;
	int		flag;

	printf("!!!test\n");
	if ((*p_tok)->next == NULL)
		return (0);
	tmp = (*p_tok)->next;
	flag = 0;
	if (ft_strncmp(tmp->word, "-n", 3) == 0)
	{
		flag = 1;
		tmp = tmp->next;
	}
	while (tmp && operater_comp(tmp->word, 0) == 0)
	{
		ft_putstr_fd(tmp->word, 1);
		tmp = tmp->next;
		if (tmp && operater_comp(tmp->word, 0) == 0)
			ft_putchar_fd(' ', 1);
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}