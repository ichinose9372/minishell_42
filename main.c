
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int main(void)
{
	char *str;
	pid_t pid;
	int status;
	t_token **p_tok;
	t_token *tok;
	// t_env	*env;

	// env = make_env();
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
				tok->next = NULL;
				tok = tokenizer(str, tok);
				*p_tok = tok;
				do_cmd(p_tok, 0, 1);
			}
			else if (pid > 0)
				wait(&status);
			else
				exit(1);
		}
		all_free_token(p_tok);
	}
	exit(0);
}
