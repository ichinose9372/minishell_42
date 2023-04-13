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
			return (new_strdup(&(stop->old_word[cnt]),
					ft_strlen(stop->old_word) - 2));
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
			return (tmp);
		}
		str2 = ft_strjoin(str, "\n");
		tmp = ft_strjoin(str3, str2);
		free(str2);
		free(str);
		free(str3);
		str3 = tmp;
	}
	return (tmp);
}

static char	*heredocu(t_token *p_tok)
{
	char	*str;
	char	*stop;

	stop = check_stop(p_tok);
	str = make_str(stop);
	free(stop);
	return (str);
}

int	heredoc_cmd(t_token *p_tok)
{
	t_pipe	pipe_data;
	char	*str;

	g_global.heredoc_flag = 0;
	signal_heredocu();
	str = heredocu(p_tok);
	if (str == NULL)
		return (-1);
	if (g_global.heredoc_flag == 1)
	{
		g_global.heredoc_flag = 0;
		return (-1);
	}
	if (pipe(pipe_data.pipe_fd) == -1)
		exit (EXIT_FAILURE);
	write(pipe_data.pipe_fd[WRITE], str, ft_strlen(str));
	close(pipe_data.pipe_fd[WRITE]);
	return (pipe_data.pipe_fd[READ]);
}
