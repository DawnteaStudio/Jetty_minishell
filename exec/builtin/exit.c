/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 06:49:29 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/11 21:34:25 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_num(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_exit(t_shell_info *shell)
{
	if (shell->tree->exp[1])
	{
		if (shell->tree->exp[2])
		{
			ft_putstr_fd("exit\njetty_shell: exit: too many arguments\n", 2);
			return (CODE_ERROR);
		}
		else if (is_num(shell->tree->exp[1]) == FALSE)
		{
			ft_putstr_fd("exit\njetty_shell: exit: ", 2);
			ft_putstr_fd(shell->tree->exp[1], 2);
			ft_putstr_fd(": numeric argument required", 2);
			return (CODE_255);
		}
		else
			g_exit_code = (ft_atoi(shell->tree->exp[1]) % 256);
	}
	clean_all(shell);
	exit(g_exit_code);
	return (g_exit_code);
}
