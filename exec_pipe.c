#include "minishell.h"

// void chiled1(t_token **p_tok, t_pipe *pipe_data, int input_fd)
// {
// 	char	**path;

// 	if (input_fd != STDIN_FILENO)
// 		dup2(input_fd, STDIN_FILENO);
// 	close(pipe_data->pipe_fd[READ]);
// 	dup2(pipe_data->pipe_fd[WRITE], STDOUT_FILENO);
// 	close(pipe_data->pipe_fd[WRITE]);
// 	if (builtin_list(p_tok) == 1)
// 	{
// 		path = token_path(p_tok);
// 		exec(path);
// 	}
// 	exit(EXIT_SUCCESS);
// }

// void chiled2(t_token **p_tok, t_pipe *pipe_data, int output_fd)
// {
// 	close(pipe_data->pipe_fd[WRITE]);
// 	while (ft_strncmp((*p_tok)->word, "|", 2) != 0)
// 		p_tok = &(*p_tok)->next;
// 	p_tok = &(*p_tok)->next;
// 	if ((*p_tok)->next == NULL || (*p_tok)->next->kind != 5)
// 		exec_cmd(p_tok, pipe_data->pipe_fd[READ], output_fd);
// 	else
// 	{
// 		close(pipe_data->pipe_fd[READ]);
// 		exec_cmd(p_tok, 0, 1);
// 	}
// }

// void exec_pipe(t_token **p_tok, int input_fd, int output_fd)
// {
// 	t_pipe	pipe_data;
// 	pid_t	pid;

// 	signal_cmd();
// 	if (pipe(pipe_data.pipe_fd) == -1)
// 		exit(EXIT_FAILURE);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(EXIT_FAILURE);
// 	if (pid == 0)
// 		chiled1(p_tok, &pipe_data, input_fd);
// 	else if (pid > 0)
// 	{
// 		chiled2(p_tok, &pipe_data, output_fd);
// 		close(pipe_data.pipe_fd[READ]);
// 		close(pipe_data.pipe_fd[WRITE]);
// 		wait(NULL);
// 	}
// }
