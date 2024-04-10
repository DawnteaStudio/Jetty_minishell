/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:07:42 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/10 09:37:50 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_is_over(unsigned long int res, int sign, const char c)
{
	if (res > LM)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	else if (res == LM)
	{
		if (sign == -1 && (c - '0') > 8)
			return (0);
		else if (sign == 1 && (c - '0') > 7)
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (ft_is_over(result, sign, str[i]) < 1)
			return (ft_is_over(result, sign, str[i]));
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
