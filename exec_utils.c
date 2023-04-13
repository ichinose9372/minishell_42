#include "minishell.h"

int	builtin_list(char **args)
{
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (builtin_pwd(args));
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		return (builtin_echo(args));
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (builtin_env(args));
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (builtin_export(args));
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (builtin_unset(args));
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (builtin_exit(args));
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
