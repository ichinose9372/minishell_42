
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

t_env	*env;

void	print_token(t_token **tok)
{
	while (tok)
	{
		printf("%s\n", (*tok)->word);
		*tok = (*tok)->next;
	}
}

int main(void)
{
	char *str;
	pid_t pid;
	int status;
	t_token **p_tok;
	t_token *tok;

	env = make_env();
	p_tok = malloc(sizeof(t_token *));
	if (p_tok == NULL)
		exit(1);
	rl_outstream = stderr;
	while (1)
	{
		str = readline("mini_shell$ ");
		if (str == NULL)
			exit(1);
		else
		{
			add_history(str);
			pid = fork();
			if (pid == 0)
			{
				tok = malloc(sizeof(t_token));
				if (tok == NULL)
				{
					printf("malloc error\n");
					exit(1);
				}
				tok->word = NULL;
				tok = tokenizer(str, tok);
				p_tok = expansion(tok);
				// *p_tok = tok;
				// do_cmd(p_tok, 0, 1);
				// print_token(p_tok);
			}
			else if (pid > 0)
				wait(&status);
			else
				exit(1);
		}
		// all_free_token(p_tok);
	}
	exit(0);
}
