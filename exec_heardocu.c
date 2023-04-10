#include "minishell.h"

static char	*make_str(char	*stop)
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*tmp;

	tmp = NULL;
	str3 = NULL;
	str = NULL;
	while (g_global.heredoc_flag == 0)
	{
		str = readline("> ");
		if (str == NULL || ft_strncmp(str, stop, (ft_strlen(stop) + 1)) == 0)
		{
			free(str);
			break ;
		}
		str2 = ft_strjoin(str, "\n");
		if (str2 == NULL)
			return (NULL);
		tmp = ft_strjoin(str3, str2);
		free(str2);
		free(str);
		free(str3);
		str3 = tmp;
	}
	return (tmp);
}

static char	*heredocu(t_token **p_tok)
{
	t_token	**tmp;
	char	*str;

	str = NULL;
	tmp = p_tok;
	while (g_global.heredoc_flag == 0)
	{
		while ((*tmp)->kind == 0)
			tmp = &(*tmp)->next;
		str = make_str((*tmp)->next->word);
		if (str == NULL)
			return (NULL);
		if ((*tmp)->next->next == NULL)
			break ;
		else
		{
			free(str);
			tmp = &(*tmp)->next;
		}
	}
	printf("{%p}\n", str);
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
	if (pipe(pipe_data.pipe_fd) == -1)
		exit (EXIT_FAILURE);
	signal_heredocu();
	str = heredocu(p_tok);
	if (str == NULL)
		return ;
	if (g_global.heredoc_flag == 1)
	{
		all_free(path);
		// free(str);
		g_global.heredoc_flag = 0;
		return ;
	}
	write(pipe_data.pipe_fd[WRITE], str, ft_strlen(str));
	dup2(pipe_data.pipe_fd[READ], STDIN_FILENO);
	close(pipe_data.pipe_fd[READ]);
	close(pipe_data.pipe_fd[WRITE]);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		exec(path);
	else
	{
		close(pipe_data.pipe_fd[WRITE]);
		free(str);
		waitpid(pid, NULL, 0);
		close(pipe_data.pipe_fd[READ]);
		dup2(g_global.fd_in, STDIN_FILENO);
		all_free(path);
	}
}
