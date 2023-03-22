/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:10 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/22 18:45:30 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"
# include "pipex.h"
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>


extern char	**environ;

typedef enum e_token_kind
{
	WORD,
	PIPE,
	OUTPUT,
	INPUT,
	ADD,
	HEREDOC,
}	t_token_kind;

typedef struct s_token
{
	char	*word;
	struct s_token	*next;
}	t_token;



#endif
