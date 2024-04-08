/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:49 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/08 21:27:06 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec_builtin(t_shell_info *shell, int builtin)
{
	if (builtin == BLT_PWD)
		return (ft_pwd());
	else if (builtin == BLT_ENV)
		return (ft_env(shell));
	return (1);
}

int ft_exec_cmd(t_shell_info *shell, char *str)
{
	int	builtin;

	builtin = is_builtin(str);
	if (builtin != FALSE)
	{
		g_exit_code = ft_exec_builtin(shell, builtin);
	}
	return (0);
}

int ft_exec(t_shell_info *shell, char *str)
{
	ft_exec_cmd(shell, str);
	return (0);
}
