/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:12:27 by stakimot          #+#    #+#             */
/*   Updated: 2023/03/25 11:12:06 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

char *new_strdup(const char *s1, int size)
{
	char *dest;
	char *src;
	size_t cnt;

	src = (char *)s1;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	cnt = 0;
	while (cnt < size)
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	dest[cnt] = '\0';
	return (dest);
}

int space_check(char *str, int start)
{
	return (str[start] == ' ' || str[start] == '\t' || str[start] == '\n');
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t cnt;

	cnt = 0;
	while (cnt < n && (s1[cnt] != '\0' || s2[cnt] != '\0'))
	{
		if (s1[cnt] != s2[cnt])
			return ((unsigned char)s1[cnt] - (unsigned char)s2[cnt]);
		cnt++;
	}
	return (0);
}
t_token *new_token(char *str, int start, int end)
{
	t_token *tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (0);
	tok->word = new_strdup(&str[start], end - start);
	if (!tok->word)
		exit(0);
	tok->next = NULL;
	return (tok);
}

void make_token(t_token **tok, char *str, int start, int end)
{
	t_token *tmp;

	if ((*tok)->word == NULL)
	{
		(*tok)->word = new_strdup(&str[start], end - start);
		if (!(*tok)->word)
			exit(0);
	}
	else
	{
		(*tok)->next = new_token(str, start, end);
		*tok = (*tok)->next;
	}
	(*tok)->next = NULL;
}

int operater_comp(char *str, int end)
{
	if (ft_strncmp(&str[end], "|", 1) == 0)
		return (1);
	else if (ft_strncmp(&str[end], "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(&str[end], ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(&str[end], "<", 1) == 0)
		return (1);
	else if (ft_strncmp(&str[end], ">", 1) == 0)
		return (1);
	else if (ft_strncmp(&str[end], ";", 1) == 0)
		return (1);
	return (0);
}

int operater_check(char *str, int *start, int *end, t_token **tok)
{
	if (operater_comp(str, *end))
	{
		if (*start != *end)
			return (1);
		else
			*end += operater_comp(str, *end);
	}
	else
		return (0);
	make_token(tok, str, *start, *end);
	while (space_check(str, *end))
		*end += 1;
	*start = *end;
	return (0);
}

int seartch_quote(char *str, int start, int *end)
{
	char c;

	c = str[*end];
	*end += 1;
	while (str[*end] != '\0' && str[*end] != c)
		*end += 1;
	if (str[*end] == '\0')
		return (1);
	return (0);
}

t_token *tokenizer(char *str, t_token *tok)
{
	t_token *tmp;
	int start;
	int end;

	start = 0;
	end = 0;
	tmp = tok;
	while (str[start])
	{
		while (str[end] != '\0' && space_check(str, end))
			end++;
		start = end;
		while (str[end] != '\0' && !space_check(str, end))
		{
			if (operater_check(str, &start, &end, &tok))
				break;
			if (str[end] == '\'' || str[end] == '\"')
			{
				if (seartch_quote(str, start, &end))
					exit(0);
			}
			end++;
		}
		if (str[start] != '\0')
			make_token(&tok, str, start, end);
	}
	return (tmp);
}

void printf_token(t_token **p_tok)
{
	while (*p_tok)
	{
		printf("%s\n", (*p_tok)->word);
		p_tok = &(*p_tok)->next;
	}
}
void all_free_token(t_token **p_toke)
{
	size_t i;

	i = 0;
	while (p_toke[i])
	{
		free(p_toke[i]);
		i++;
	}
}

char	**token_path(t_token **p_tok)
{
	char	**argv;
	int		i;
	int		size;
	t_token	**tmp_tok;

	tmp_tok = p_tok;
	size = 0;
	while ((*tmp_tok))
	{
		if (ft_strncmp((*tmp_tok)->word, "|", 1) == 0 || ft_strncmp((*tmp_tok)->word, ">", 1) == 0 || ft_strncmp((*tmp_tok)->word, ">>", 2) == 0)
			break ;
		size++;
		tmp_tok = &(*tmp_tok)->next;
	}
	argv = malloc(sizeof(char *) * (size + 1));
	tmp_tok = p_tok;
	i = 0;
	while (i < size)
	{
		argv[i] = ft_strdup((*tmp_tok)->word);
		i++;
		tmp_tok = &(*tmp_tok)->next;
	}
	argv[size] = NULL;
	argv[0] = make_path(argv[0], environ);
	return (argv);

}

int	check_no_operation(t_token **p_tok)
{
	t_token	**tmp;
	int		ret;

	tmp = p_tok;
	ret = 0;
	while ((*tmp))
	{
		if (ft_strncmp((*tmp)->word, "|", 1) == 0)
		{
			ret = 1;
			return (ret);
		}
		else if (ft_strncmp((*tmp)->word, ">", 1) == 0)
		{
			if (ft_strncmp((*tmp)->word, ">>", 2) == 0)
			{
				ret = 3;
				return (ret);
			}
			else
			{
				ret = 2;
				return (ret);
			}
		}
		tmp = &(*tmp)->next;
	}
	return (ret);
}

void do_cmd(t_token **p_tok, int input_fd, int output_fd)
{
	char	**path;
	int		fd[2];
	pid_t	pid;
	t_token	*next_tok;
	int		f_fd;

	if (check_no_operation(p_tok) == 1)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (input_fd != STDIN_FILENO)
				dup2(input_fd, STDIN_FILENO);
			close(fd[READ]);
			dup2(fd[WRITE], STDOUT_FILENO);
			close(fd[WRITE]);
			path = token_path(p_tok);
			execve(path[0], path, environ);
			perror("exec");
			exit(EXIT_FAILURE);
		}
		if (pid > 0)
		{
			close(fd[WRITE]);
			while (ft_strncmp((*p_tok)->word, "|", 1) != 0)
				p_tok = &(*p_tok)->next;
			p_tok = &(*p_tok)->next;
			do_cmd(p_tok, fd[READ], output_fd);
			close(fd[READ]);
			waitpid(pid, NULL, 0);
		}
	}
	else if (check_no_operation(p_tok) == 0)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (input_fd != 0)
				dup2(input_fd, STDIN_FILENO);
			if (output_fd != 1)
				dup2(output_fd, STDOUT_FILENO);
			path = token_path(p_tok);
			execve(path[0], path, environ);
			perror("exec");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
			waitpid(pid, NULL, 0);
	}
	else if (check_no_operation(p_tok) == 2 || check_no_operation(p_tok) == 3)
	{
		t_token	**tmp;

		tmp = p_tok;
		if (check_no_operation(p_tok) == 3)
		{
			while (ft_strncmp((*p_tok)->word, ">>", 2) != 0)
				p_tok = &(*p_tok)->next;
			p_tok = &(*p_tok)->next;
			f_fd = file_open_wrt_add((*p_tok)->word);
		}
		else
		{
			while (ft_strncmp((*p_tok)->word, ">", 1) != 0)
				p_tok = &(*p_tok)->next;
			p_tok = &(*p_tok)->next;
			f_fd = file_open_wrt((*p_tok)->word);
		}
		if (input_fd != 0)
			dup2(input_fd, STDIN_FILENO);
		dup2(f_fd, STDOUT_FILENO);
		path = token_path(tmp);
		execve(path[0], path, environ);
	}
}


int main(void)
{
	char *str;
	pid_t pid;
	int status;
	int i;
	t_token **p_tok;
	t_token *tok;

	p_tok = malloc(sizeof(t_token *));
	if (p_tok == NULL)
		exit(1);
	rl_outstream = stderr;
	while (1)
	{
		str = readline("mini_shell$ ");
		if (str == NULL)
			exit(1);
		else
		{
			add_history(str);
			pid = fork();
			if (pid == 0)
			{
				tok = malloc(sizeof(t_token));
				if (tok == NULL)
					exit(1);
				tok = tokenizer(str, tok);
				*p_tok = tok;
				do_cmd(p_tok, 0, 1);
			}
			else if (pid > 0)
				wait(&status);
			else
				exit(1);
		}
		all_free_token(p_tok);
	}
	exit(0);
}
