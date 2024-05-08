/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:41:52 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/09 00:33:29 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_null(t_shell_info *shell, t_tree *tree)
{
	if (is_no_quotes(shell->str) == FALSE)
		return (putstr_error("", CODE_NOT_FOUND, ERR_CMD_NOT_FND));
	else if (tree->exp[1] == NULL)
		return (CODE_SUCCESS);
	rearrange_exp(tree, 0);
	free(tree->cmd);
	tree->cmd = ft_strdup(tree->exp[0]);
	return (ft_exec_cmd(shell, tree, NULL, FALSE));
}
