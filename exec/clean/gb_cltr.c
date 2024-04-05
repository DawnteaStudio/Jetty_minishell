/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_cltr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:38:49 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/05 14:55:32 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	del(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

char	*heap_handler(char *ptr)
{
	static	t_list	*list;

	if (ptr == NULL)
		ft_lstclear(&list, del);
	else
		ft_lstadd_back(&list, ft_lstnew(ptr));
	return (ptr);
}
