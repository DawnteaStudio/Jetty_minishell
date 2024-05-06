/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:39:02 by erho              #+#    #+#             */
/*   Updated: 2024/05/06 21:49:48 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cnt_exp(char **exp)
{
	int	i;

	i = 0;
	while (exp[i] != NULL)
		i++;
	return (i);
}

t_tree	*find_last_right(t_tree *tree)
{
	while (tree->right != NULL)
		tree = tree->right;
	return (tree);
}

void	cpy_new_exp(char **new_exp, char **exp, char **tmp, int exp_len)
{
	int	new_idx;
	int	exp_idx;
	int	tmp_idx;

	new_idx = 0;
	exp_idx = 0;
	tmp_idx = 0;
	while (exp_idx < exp_len)
		new_exp[new_idx++] = exp[exp_idx++];
	if (exp[exp_idx] != NULL)
	{
		new_exp[new_idx++] = str_join(exp[exp_idx], tmp[tmp_idx]);
		free(tmp[tmp_idx++]);
	}
	while (tmp[tmp_idx] != NULL)
		new_exp[new_idx++] = tmp[tmp_idx++];
}
