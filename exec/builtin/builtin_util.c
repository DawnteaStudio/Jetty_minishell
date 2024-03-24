/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:02:59 by sewopark          #+#    #+#             */
/*   Updated: 2024/03/24 22:19:59 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	else if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "exit"))
		return (TRUE);
	else
		return (FALSE);
}
