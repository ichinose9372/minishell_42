#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

t_env	**env;

void	print_token(t_token **tok)
{
	t_token	*tmp;

	tmp = *tok;
	if (tok == NULL)
	{
		printf("after free all\n");
	}
	while (tmp)
	{
		printf("tok:%s\t%p\n", tmp->word, tmp->next);
		tmp = tmp->next;
	}
}


void	minishell_2(t_token **p_tok, char *str)
{
	pid_t	pid;
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (tok == NULL)
		exit(EXIT_FAILURE);
	tok->word = NULL;
	tok = tokenizer(str, tok);
	print_token(p_tok);
	expansion(tok, p_tok);
	if (builtin_list(p_tok) == 1)
	{
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			exec_cmd(p_tok, 0, 1);
		else
			wait(NULL);
	}
}

void	minishell(void)
{
	char	*str;
	t_token	**p_tok;

	make_env();
	rl_outstream = stderr;
	while (1)
	{
		p_tok = malloc(sizeof(t_token *));
		if (p_tok == NULL)
			exit(EXIT_FAILURE);
		str = readline("mini_shell$ ");
		if (str == NULL)
			exit(1);
		else if (*str == '\0')
			free(p_tok);
		else
		{
			add_history(str);
			minishell_2(p_tok, str);
		}
		all_free_token(p_tok);
		print_token(p_tok);
	}
	exit(0);
}

int	main(void)
{
	minishell();
}
