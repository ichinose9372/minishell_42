#include "minishell.h"

char	*make_str(t_token **tmp)
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
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(str, (*tmp)->next->word, ft_strlen(str)) == 0)
			break ;
		str2 = ft_strjoin(str, linefeed);
		str3 = ft_strjoin(str3, str2);
	}
	return (str3);
}

void	exec_heardocu(t_token **p_tok)
{
	pid_t	pid;
	t_pipe	pipe_data;
	t_token	**tmp;
	char	*str;

	pid = fork();
	signal_heredocu();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal_heredocu();
		tmp = p_tok;
		while (ft_strncmp((*tmp)->word, "<<", 2) != 0)
			tmp = &(*tmp)->next;
		pipe(pipe_data.pipe_fd);
		str = make_str(tmp);
		write(pipe_data.pipe_fd[WRITE], str, ft_strlen(str));
		dup2(pipe_data.pipe_fd[READ], STDIN_FILENO);
		close(pipe_data.pipe_fd[READ]);
		close(pipe_data.pipe_fd[WRITE]);
		exec(p_tok);
	}
	else
		wait(NULL);
}
