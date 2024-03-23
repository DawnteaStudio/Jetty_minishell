/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:32:42 by erho              #+#    #+#             */
/*   Updated: 2024/01/12 20:47:46 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dest_len = 0;
	if (dest != NULL)
		dest_len = ft_strlen(dest);
	dest += dest_len;
	src_len = ft_strlen(src);
	if (len <= dest_len)
		return (len + src_len);
	while (src[i] && dest_len + i + 1 < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
