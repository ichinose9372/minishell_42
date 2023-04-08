#include "minishell.h"

t_token	*new_tok_pipe(char *str)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	tok->word = ft_strdup(str);
	tok->next = NULL;
	return (tok);
}

void	chiled1(t_token **p_tok, t_pipe *pipe_data, int input_fd)
{
	t_token	**new_tok;
	t_token	*tmp;

	tmp = global.top_tok;
	new_tok = (t_token **)malloc(sizeof(t_token *));
	*new_tok = new_tok_pipe(tmp->word);
	tmp = tmp->next;
	while (tmp->kind != 1)
	{
		(*new_tok)->next = new_tok_pipe(tmp->word);
		printf("2:%s\n", (*new_tok)->next->word);
		*new_tok = (*new_tok)->next;
		tmp = tmp->next;
	}
	if (input_fd != STDIN_FILENO)
		dup2(input_fd, STDIN_FILENO);
	close(pipe_data->pipe_fd[READ]);
	dup2(pipe_data->pipe_fd[WRITE], STDOUT_FILENO);
	printf("test111\n");
	close(pipe_data->pipe_fd[WRITE]);
	if (builtin_list(p_tok) == 1)
	{
		exec_cmd(new_tok, input_fd, pipe_data->pipe_fd[WRITE]);
	}
	exit (EXIT_SUCCESS);
}

void	chiled2(t_token **p_tok, t_pipe *pipe_data, int output_fd)
{
	close(pipe_data->pipe_fd[WRITE]);
	while (ft_strncmp((*p_tok)->word, "|", 2) != 0)
		p_tok = &(*p_tok)->next;
	p_tok = &(*p_tok)->next;
	exec_cmd(p_tok, pipe_data->pipe_fd[READ], output_fd);
}

void	exec_pipe(t_token **p_tok, int input_fd, int output_fd)
{
	t_pipe	pipe_data;
	pid_t	pid;

	signal_cmd();
	if (pipe(pipe_data.pipe_fd) == -1)
		exit (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		chiled1(p_tok, &pipe_data, input_fd);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		chiled2(p_tok, &pipe_data, output_fd);
		close(pipe_data.pipe_fd[READ]);
	}
}
