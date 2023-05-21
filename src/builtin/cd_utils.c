/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:47:48 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/21 16:52:54 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*home_path(void)
{
	char	*home;
	t_env	**tmp;

	tmp = g_global.env;
	while (ft_strncmp((*tmp)->name, "HOME", 5) != 0)
		tmp = &(*tmp)->next;
	home = ft_strdup((*tmp)->value);
	if (home == NULL)
		return (NULL);
	return (home);
}

void	remake_pwd(char	*new_path)
{
	t_env	**tmp;

	tmp = g_global.env;
	while (ft_strncmp((*tmp)->name, "PWD", 4) != 0)
		tmp = &(*tmp)->next;
	free((*tmp)->value);
	(*tmp)->value = ft_strdup(new_path);
}

int	serch_home(void)
{
	t_env	*tmp;

	tmp = *g_global.env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "HOME", 5) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	*my_getcwd(char *buf, size_t length)
{
	size_t	size;
	t_env	*tmp;

	tmp = *g_global.env;
	while (tmp && ft_strncmp(tmp->name, "PWD", 4) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	size = 0;
	while (size < length - 1 && tmp->value[size])
	{
		buf[size] = tmp->value[size];
		size++;
	}
	buf[size] = '\0';
	return (buf);
}

char	*cd_make_path(char *path_name, char	*word)
{
	char	*new_path;
	char	*tmp;

	if (path_name[0] == '/' && !path_name[1])
		tmp = ft_strtrim(word, "/");
	else
		tmp = ft_strjoin("/", word);
	new_path = ft_strjoin(path_name, tmp);
	if (!new_path)
		exit(EXIT_FAILURE);
	free(tmp);
	return (new_path);
}
