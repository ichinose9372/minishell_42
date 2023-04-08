#include "minishell.h"

static char	*make_str(char	*stop)
{
	char	*str;
	char	*linefeed;
	char	*str2;
	char	*str3;
	char	*tmp;

	linefeed = "\n";
	str3 = malloc(sizeof(char));
	if (str3 == NULL)
		exit(EXIT_FAILURE);
	str3 = "";
	while (g_global.heredoc_flag == 0)
	{
		str = readline("> ");
		if (str == NULL || ft_strncmp(str, stop, (ft_strlen(stop) + 1)) == 0)
			break ;
		str2 = ft_strjoin(str, linefeed);
		if (str2 == NULL)
			return (NULL);
		tmp = str3;
		free(str3);
		str3 = ft_strjoin(tmp, str2);
		if (str3 == NULL)
		{
			free(str2);
			return (NULL);
		}
		free(tmp);
		free(str);
		free(str2);
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
		if (str == NULL)
			return (NULL);
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
	char	**path;

	path = token_path(p_tok);
	g_global.heredoc_flag = 0;
	str = NULL;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal_heredocu();
		if (pipe(pipe_data.pipe_fd) == -1)
			exit (EXIT_FAILURE);
		str = heredocu(p_tok, str);
		if (str == NULL)
			exit(EXIT_FAILURE);
		if (g_global.heredoc_flag == 1)
			exit(0);
		write(pipe_data.pipe_fd[WRITE], str, ft_strlen(str));
		dup2(pipe_data.pipe_fd[READ], STDIN_FILENO);
		close(pipe_data.pipe_fd[READ]);
		close(pipe_data.pipe_fd[WRITE]);
		exec(path);
	}
	else
	{
		wait(NULL);
		all_free(path);
	}
}
