/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:12:27 by stakimot          #+#    #+#             */
/*   Updated: 2023/03/22 18:35:13 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

// typedef struct s_token
// {
// 	char			*word;
// 	struct s_token	*next;
// }	t_token;

// typedef enum e_token_quote
// {
// 	OUT_QUOTE,
// 	SINGLE_QUOTE,
// 	DOUBLE_QUOTE,
// }	t_token_quote;

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
int tokensize(t_token *p_tok)
{
	int i;

	i = 0;
	while (p_tok)
	{
		p_tok = p_tok->next;
		i++;
	}
	return (i);
}

// void do_cmd(t_token **p_tok)
// {
// 	char	**path;
// 	int		fd[2];
// 	pid_t	pid;
// 	int		f_fd;
// 	t_token	**tmp;

// 	tmp = p_tok;
// 	if ((*p_tok)->word && (*p_tok)->next == NULL)
// 	{
// 		path = split_arg((*p_tok)->word, environ);
// 		execve(path[0], path, environ);
// 	}
// 	else
// 	{
// 		if (ft_strncmp((*p_tok)->next->word, "|", 1) == 0)
// 		{
// 			pipe(fd);
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				close(fd[READ]);
// 				dup2(fd[WRITE], STDOUT_FILENO);
// 				close(fd[WRITE]);
// 				path = split_arg((*p_tok)->word, environ);
// 				execve(path[0], path, environ);
// 			}
// 			else if (pid > 0)
// 			{
// 				*p_tok = (*p_tok)->next->next;
// 				close(fd[WRITE]);
// 				dup2(fd[READ], STDIN_FILENO);
// 				close(fd[READ]);
// 				path = split_arg((*p_tok)->word, environ);
// 				execve(path[0], path, environ);
// 			}
// 		}
// 		else if (ft_strncmp((*p_tok)->next->word, ">", 1) == 0
// 			&& (*p_tok)->next->next != NULL)
// 		{
// 			f_fd = file_open_wrt((*p_tok)->next->next->word);
// 			dup2(f_fd, STDOUT_FILENO);
// 			close(f_fd);
// 			path = split_arg((*p_tok)->word, environ);
// 			execve(path[0], path, environ);
// 		}
// 		else if (ft_strncmp((*p_tok)->word, "<", 1) == 0)
// 		{
// 			path = split_arg((*p_tok)->next->next->word, environ);
// 			if (path[0] == NULL)
// 				exit(EXIT_FAILURE);
// 			f_fd = file_open_rd((*p_tok)->next->word);
// 			dup2(f_fd, STDIN_FILENO);
// 			close(f_fd);
// 			execve(path[0], path, environ);
// 		}
// 		else
// 			printf("aaaa\n");
// 	}
// }

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
				do_cmd(p_tok);
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
