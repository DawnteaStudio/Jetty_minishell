/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:39:02 by erho              #+#    #+#             */
/*   Updated: 2024/05/05 14:22:45 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**join_exp(char **tree_exp, char **tmp)
{
	int		cnt;
	char	**new_exp;

	cnt = cnt_exp(tree_exp) + cnt_exp(tmp);
	new_exp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (new_exp == NULL)
		exit(1);
	new_exp[cnt] = NULL;
	cpy_new_exp(new_exp, tree_exp, tmp);
	free(tree_exp);
	free(tmp);
	return (new_exp);
}

t_tree	*find_last_right(t_tree *tree)
{
	while (tree->right != NULL)
		tree = tree->right;
	return (tree);
}

void	cpy_new_exp(char **new_exp, char **exp, char **tmp)
{
	int	new_idx;
	int	idx;

	new_idx = 0;
	idx = 0;
	while (exp[idx])
		new_exp[new_idx++] = exp[idx++];
	free(exp[idx]);
	idx = 0;
	while (tmp[idx])
		new_exp[new_idx++] = tmp[idx++];
	free(tmp[idx]);
}
