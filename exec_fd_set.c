#include "minishell.h"

int	set_input(t_token **p_tok)
{
	int	in;

	*p_tok = (*p_tok)->next;
	in = file_open_rd((*p_tok)->word);
	return (in);
}

int	set_output(t_token **p_tok)
{
	int	out;

	*p_tok = (*p_tok)->next;
	out = file_open_wrt((*p_tok)->word);
	return (out);
}

int	set_add(t_token **p_tok)
{
	int	out;

	*p_tok = (*p_tok)->next;
	out = file_open_wrt_add((*p_tok)->word);
	return (out);
}

void	set_fd(t_token *p_tok, int *in, int *out)
{
	if ((p_tok)->kind == INPUT)
		*in = set_input(&p_tok);
	else if ((p_tok)->kind == OUTPUT)
		*out = set_output(&p_tok);
	else if ((p_tok)->kind == ADD)
		*out = set_add(&p_tok);
	else if ((p_tok)->kind == HEREDOC)
	{
		p_tok = (p_tok)->next;
		*in = heredoc_cmd(p_tok);
	}
}

void	init_pipe_setfd(int *flag, int *output_fd, t_pipe *pipe_data)
{
	*flag = 1;
	if (pipe(pipe_data->pipe_fd) == -1)
		exit(1);
	*output_fd = pipe_data->pipe_fd[WRITE];
}
