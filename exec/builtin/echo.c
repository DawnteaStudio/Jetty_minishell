/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 06:08:50 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/10 07:16:54 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//char **node is node's d_array;

#include "../include/minishell.h"

int	ft_option(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (FALSE);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_echo(t_shell_info *shell)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (shell->d_array[i] != NULL && ft_option(shell->d_array[i]) == 1)
	{
		option = 1;
		i++;
	}
	while (shell->d_array[i])
	{
		ft_putstr_fd(shell->d_array[i], 1);
		if (shell->d_array[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	return (CODE_SUCCESS);
}
