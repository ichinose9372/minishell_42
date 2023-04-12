#include "minishell.h"

int	builtin_list(t_token **p_tok)
{
	if (ft_strncmp((*p_tok)->word, "pwd", 3) == 0)
		return (builtin_pwd(p_tok));
	else if (ft_strncmp((*p_tok)->word, "echo", 4) == 0)
		return (builtin_echo(p_tok));
	else if (ft_strncmp((*p_tok)->word, "env", 3) == 0)
		return (builtin_env(p_tok));
	else if (ft_strncmp((*p_tok)->word, "export", 6) == 0)
		return (builtin_export(p_tok));
	else if (ft_strncmp((*p_tok)->word, "unset", 5) == 0)
		return (builtin_unset(p_tok));
	else if (ft_strncmp((*p_tok)->word, "exit", 4) == 0)
		return (builtin_exit(p_tok));
	return (1);
}

char	**convet_environ()
{
	int		cnt;
	t_env	*env;
	char	*tmp;
	char	**mini_environ;

	cnt = 0;
	env = *g_global.env;
	while (env)
	{
		if (env->value)
			cnt++;
		env = env->next;
	}
	mini_environ = (char **)malloc(sizeof(char *) * cnt + 1);
	if (!mini_environ)
		exit(1);
	env = *g_global.env;
	cnt = 0;
	while (env)
	{
		if (env->value)
		{
			mini_environ[cnt] = ft_strdup(env->name);
			tmp = ft_strjoin(mini_environ[cnt], "=");
			free(mini_environ[cnt]);
			mini_environ[cnt] = tmp;
			tmp = ft_strjoin(mini_environ[cnt], env->value);
			free(mini_environ[cnt]);
			mini_environ[cnt] = tmp;
			cnt++;
		}
		env = env->next;
	}
	mini_environ[cnt] = NULL;
	return (mini_environ);
}

void	exec(char	**path)
{
	char	**mini_environ;

	mini_environ = convet_environ();
	execve(path[0], path, mini_environ);
	perror("exec");
	exit (1);
}
