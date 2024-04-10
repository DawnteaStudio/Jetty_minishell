/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:02:28 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/10 06:26:44 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_restore_fd(t_shell_info *shell)
{
	dup2(shell->backup_stdin, 0);
	dup2(shell->backup_stdout, 1);
}
