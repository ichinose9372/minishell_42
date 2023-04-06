/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:21:27 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/04/05 11:39:27 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*ndptr;

	ndptr = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (ndptr -> next != NULL)
		ndptr = ndptr -> next;
	ndptr -> next = new;
}
