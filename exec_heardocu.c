#include "minishell.h"

char	*check_stop(t_token *stop)
{
	size_t	cnt;

	cnt = 0;
	if (stop->old_word[0] == '\"' || stop->old_word[0]== '\"')
		cnt++;
	if (stop->word[0] != stop->old_word[cnt])
	{
		if (cnt == 1)
			return (new_strdup(&(stop->old_word[cnt]), ft_strlen(stop->old_word) - 2));
		return (ft_strdup(stop->old_word));
	}
	return (ft_strdup(stop->word));
}

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
		if (!str)
			break ;
		if (ft_strncmp(str, stop, (ft_strlen(stop) + 1)) == 0)
		{
			free(str);
			break ;
		}
		expansion_heredoc(&str);
		str2 = ft_strjoin(str, "\n");
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
	char	*stop;

	str = NULL;
	tmp = p_tok;
	while (g_global.heredoc_flag == 0)
	{
		while ((*tmp)->kind == 0)
			tmp = &(*tmp)->next;
		stop = check_stop((*tmp)->next);
		str = make_str(stop);
		free(stop);
		if (str == NULL)
			return (NULL);
		if ((*tmp)->next->next == NULL || (*tmp)->next->next->next == NULL || (*tmp)->next->next->kind != 0)
			break ;
		else
		{
			free(str);
			tmp = &(*tmp)->next;
		}
	}
	return (str);
}

void	exec_heardocu(t_token **p_tok)
{
	pid_t	pid;
	t_pipe	pipe_data;
	char	*str;
	char	**path;
	t_token **tmp;

	if ((*p_tok)->next != NULL && (*p_tok)->next->kind == 5)
	{
		path = token_path(p_tok);
		if (!path)
			return ;
	}
	else
	{
		tmp = p_tok;
		while ((*tmp)->next != NULL)
			tmp = &(*tmp)->next;
		path = token_path(tmp);
		if (!path)
			return ;
	}
	g_global.heredoc_flag = 0;
	if (pipe(pipe_data.pipe_fd) == -1)
		exit (EXIT_FAILURE);
	signal_heredocu();
	str = heredocu(p_tok);
	if (str == NULL)
	{
		all_free(path);
		return ;
	}
	if (g_global.heredoc_flag == 1)
	{
		all_free(path);
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
