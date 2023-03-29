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
		printf("tok:%s\t%p\n", tmp->word, tmp->next);
		tmp = tmp->next;
	}
}

int	main(void)
{
	char	*str;
	t_token	**p_tok;
	t_token	*tok;
	pid_t	pid;

	make_env();
	rl_outstream = stderr;
	while (1)
	{
		p_tok = (t_token **)malloc(sizeof(t_token *));
		if (p_tok == NULL)
			exit(1);
		str = readline("mini_shell$ ");
		if (str == NULL)
			exit(1);
		else if (*str == '\0')
		{
			free(p_tok);
		}
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
			if (ft_strncmp((*p_tok)->word, "exit", 4) == 0)
				builtin_exit(p_tok);
			else if (ft_strncmp((*p_tok)->word, "cd", 3) == 0)
				builtin_cd(p_tok);
			else if (ft_strncmp((*p_tok)->word, "export", 6) == 0)
				builtin_export(p_tok);
			else
			{
				pid = fork();
				if (pid == 0)
					do_cmd(p_tok, 0, 1);
				else
					wait(NULL);
			}
			all_free_token(p_tok);
		}
	}
	exit(0);
}
