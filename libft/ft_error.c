/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:16:28 by erho              #+#    #+#             */
/*   Updated: 2024/01/18 19:25:55 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_error(int error_no)
{
	if (error_no == MEMORY)
	{
		ft_putstr_fd("memory allocation failed\n", 2);
		exit(1);
	}
	else
	{
		ft_putstr_fd("writing failed\n", 2);
		exit(1);
	}
}
