/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:52:05 by yichinos          #+#    #+#             */
/*   Updated: 2023/03/13 16:33:01 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("mini_shell ");
		if (str == NULL)
			exit (1);
		else
			add_history(str);
		printf("str = %s\n", str);
		free (str);
	}
	exit(0);
}
