/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:13:56 by erho              #+#    #+#             */
/*   Updated: 2024/01/18 19:24:05 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		ft_error(MEMORY);
	res[0] = '\0';
	if (len == 0)
		return (res);
	ft_strlcat(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, len + 1);
	return (res);
}
