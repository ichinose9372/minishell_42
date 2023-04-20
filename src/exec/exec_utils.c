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
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (builtin_cd(args));
	return (1);
}

int	builtin_check(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (1);
	return (0);
}

void	exec(char	**path)
{
	char	**mini_environ;

	mini_environ = convet_environ();
	execve(path[0], path, mini_environ);
	perror("exec");
	exit (1);
}

void	swich_fd_check_builtin(int input_fd, int output_fd, char **args)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	if (builtin_list(args) == 0)
	{
		g_global.status = 0;
		all_free(args);
		return ;
	}
	else
	{
		g_global.status = 1;
		return ;
	}
}
