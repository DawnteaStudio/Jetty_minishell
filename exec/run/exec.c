/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:49 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/11 23:18:36 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec_cmd(t_shell_info *shell, char *str)
{
	int	builtin;

	builtin = is_builtin(str);
	if (builtin != FALSE)
	{
		g_exit_code = ft_exec_builtin(shell, builtin);
	}
	else
		ft_exec_node(shell, str);
	return (0);
}

int	ft_exec(t_shell_info *shell, char *str)
{
	ft_exec_cmd(shell, str);
	return (0);
}
