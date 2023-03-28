#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

t_env	**env;

void	print_token(t_token **tok)
{
	t_token	*tmp;

	tmp = *tok;
	while (tmp)
	{
		printf("tok:%s\n", tmp->word);
		tmp = tmp->next;
	}
}

int	main(void)
{
	char	*str;
	t_token	**p_tok;
	t_token	*tok;

	p_tok = (t_token **)malloc(sizeof(t_token *));
	if (p_tok == NULL)
		exit(1);
	make_env();
	rl_outstream = stderr;
	while (1)
	{
		str = readline("mini_shell$ ");
		if (str == NULL)
			exit(1);
		else
		{
			tok = malloc(sizeof(t_token));
			if (tok == NULL)
			{
				printf("malloc error\n");
				exit(1);
			}
			add_history(str);
			tok->word = NULL;
			tok = tokenizer(str, tok);
			expansion(tok, p_tok);
			do_cmd(p_tok, 0, 1);
		}
		all_free_token(p_tok);
	}
	exit(0);
}
