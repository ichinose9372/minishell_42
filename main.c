#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

void	print_token(t_token **p_tok)
{
	t_token	**tmp;

	tmp = p_tok;
	while (*tmp)
	{
		printf("[w=%s]\n[ow=%s]\n", (*tmp)->word, (*tmp)->old_word);
		tmp = &(*tmp)->next;
	}
}

int	minishell_2(t_token **p_tok, char *str)
{
	t_token	*tok;

	(void)p_tok;
	tok = malloc_error(sizeof(t_token));
	tok->word = NULL;
	tok->old_word = NULL;
	tok = tokenizer(str, tok);
	// print_token(&tok);
	// return (0);
	if (tok == NULL)
		return (0);
	if (tok->word == NULL)
	{
		free(tok);
		return (1);
	}
	expansion(tok, p_tok);
	if (ft_strncmp((*p_tok)->word, "cd", 3) == 0)
		builtin_cd(p_tok);
	else if (ft_strncmp((*p_tok)->word, "exit", 5) == 0)
		builtin_exit(p_tok);
	else
		exec_cmd(p_tok, 0, 1);
	return (0);
}

void	minishell(void)
{
	char	*str;
	t_token	**p_tok;

	rl_outstream = stderr;
	while (1)
	{
		p_tok = (t_token **)malloc_error(sizeof(t_token *));
		signal_one();
		str = readline("mini_shell$ ");
		signal(SIGINT, SIG_IGN);
		if (str == NULL)
			exit(EXIT_SUCCESS);
		else if (*str == '\0')
			free(p_tok);
		else
		{
			add_history(str);
			if (minishell_2(p_tok, str) == 1)
				free(p_tok);
			else
				all_free_token(p_tok);
		}
		free(str);
		dup2(g_global.fd_in, STDIN_FILENO);
		dup2(g_global.fd_out, STDOUT_FILENO);
	}
	exit(0);
}

int	main()
{
	// (void)argc;
	// (void)argv;
	// for (size_t i = 0; envp[i]; i++)
	// {
	// 	printf("%s\n", envp[i]);
	// }
	// printf("test\n");
	init_minishell();
	minishell();
}
