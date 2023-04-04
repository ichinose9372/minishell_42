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
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (tok == NULL)
		exit(EXIT_FAILURE);
	tok->word = NULL;
	tok = tokenizer(str, tok);
	if (tok->word == NULL)
		return ;
	expansion(tok, p_tok);
	if (ft_strncmp((*p_tok)->word, "cd", 3) == 0)
		builtin_cd(p_tok);
	else if (ft_strncmp((*p_tok)->word, "exit", 5) == 0)
		builtin_exit(p_tok);
	else
		exec_cmd(p_tok, 0, 1);
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
			exit(1);
		signal_one();
		str = readline("mini_shell$ ");
		signal(SIGINT, SIG_IGN);
		if (str == NULL)
			exit(1);
		else if (*str == '\0')
			free(p_tok);
		else
		{
			add_history(str);
			minishell_2(p_tok, str);
			all_free_token(p_tok);
		}
		free(str);
	}
	exit(0);
}

int	main(void)
{
	init_minishell();
	minishell();
}
