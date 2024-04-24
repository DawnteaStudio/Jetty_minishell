/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:39:02 by erho              #+#    #+#             */
/*   Updated: 2024/04/25 03:06:15 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*find_last_right(t_tree *tree)
{
	while (tree->right != NULL)
		tree = tree->right;
	return (tree);
}

char	**set_exp(t_token *tmp)
{
	int		idx;
	int		cnt;
	char	**res;

	cnt = 0;
	while (tmp[cnt].str)
		cnt++;
	res = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (res == NULL)
		exit(1);
	idx = 0;
	while (tmp[idx].str)
	{
		res[idx] = ft_strdup(tmp[idx].str);
		idx++;
	}
	res[idx] = NULL;
	return (res);
}

void	cpy_new_exp(char **new_exp, char **exp, char **tmp)
{
	int	new_idx;
	int	idx;

	new_idx = 0;
	idx = 0;
	while (exp[idx])
		new_exp[new_idx++] = exp[idx++];
	idx = 0;
	while (tmp[idx])
		new_exp[new_idx++] = tmp[idx++];
}
