/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:42:30 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/04 17:42:42 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t	i;
	char	*s;

	i = 0;
	s = ptr;
	while (i < num)
	{
		s[i] = value;
		i++;
	}
	return (ptr);
}
