/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:12:16 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/11 22:03:17 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	end;

	end = 0;
	s_len = ft_strlen(s);
	if (start < s_len)
		end = s_len - start;
	if (end > len)
		end = len;
	str = (char *)malloc(end + 1);
	if (str == NULL)
		ft_error(MEMORY);
	if (start >= s_len)
		start = s_len;
	ft_strlcpy(str, s + start, end + 1);
	return (str);
}
