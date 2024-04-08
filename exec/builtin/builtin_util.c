/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:02:59 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/08 21:17:38 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	else if (!ft_strcmp(cmd, "echo"))
		return (BLT_ECHO);
	else if (!ft_strcmp(cmd, "cd"))
		return (BLT_CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (BLT_PWD);
	else if (!ft_strcmp(cmd, "export"))
		return (BLT_EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (BLT_UNSET);
	else if (!ft_strcmp(cmd, "env"))
		return (BLT_ENV);
	else if (!ft_strcmp(cmd, "exit"))
		return (BLT_EXIT);
	else
		return (FALSE);
}
