#include "minishell.h"

static char	*make_str(char	*stop)
{
	char	*str;
	char	*linefeed;
	char	*str2;
	char	*str3;

	linefeed = "\n";
	str3 = malloc(sizeof(char));
	if (str3 == NULL)
		exit(EXIT_FAILURE);
	str3 = "";
	while (global.heredoc_flag == 0)
	{
		str = readline("> ");
		if (str == NULL || ft_strncmp(str, stop, (ft_strlen(stop) + 1)) == 0)
			break ;
		str2 = ft_strjoin(str, linefeed);
		str3 = ft_strjoin(str3, str2);
	}
	return (str3);
}

static char	*heredocu(t_token **p_tok, char	*str)
{
	t_token	**tmp;

	tmp = p_tok;
	while (1)
	{
		while (ft_strncmp((*tmp)->word, "<<", 2) != 0)
			tmp = &(*tmp)->next;
		str = make_str((*tmp)->next->word);
		if ((*tmp)->next->next == NULL)
			break ;
		else
			tmp = &(*tmp)->next;
	}
	return (str);
}

void	exec_heardocu(t_token **p_tok)
{
	pid_t	pid;
	t_pipe	pipe_data;
	char	*str;

	global.heredoc_flag = 0;
	str = NULL;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal_heredocu();
		pipe(pipe_data.pipe_fd);
		str = heredocu(p_tok, str);
		if (global.heredoc_flag == 1)
			exit(0);
		write(pipe_data.pipe_fd[WRITE], str, ft_strlen(str));
		dup2(pipe_data.pipe_fd[READ], STDIN_FILENO);
		close(pipe_data.pipe_fd[READ]);
		close(pipe_data.pipe_fd[WRITE]);
		exec(p_tok);
	}
	else
		wait(NULL);
}
