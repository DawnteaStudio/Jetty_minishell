/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:32:09 by erho              #+#    #+#             */
/*   Updated: 2024/01/18 19:23:59 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *str)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		ft_error(MEMORY);
	i = 0;
	while (i <= len)
	{
		res[i] = ((char *)str)[i];
		i++;
	}
	return (res);
}
