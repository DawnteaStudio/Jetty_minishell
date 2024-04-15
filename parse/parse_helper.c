/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:17:11 by erho              #+#    #+#             */
/*   Updated: 2024/04/16 01:06:31 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].str)
	{
		free(tokens[i].str);
		i++;
	}
	free(tokens);
}

void	free_node(t_tree **tree)
{
	int	idx;

	if ((*tree)->cmd != NULL)
		free((*tree)->cmd);
	if ((*tree)->redir != NULL)
		free((*tree)->redir);
	if ((*tree)->redir_info != NULL)
		free((*tree)->redir_info);
	if ((*tree)->exp != NULL)
	{
		idx = 0;
		while ((*tree)->exp[idx] != NULL)
		{
			free((*tree)->exp[idx]);
			idx++;
		}
		free((*tree)->exp);
	}
	if ((*tree)->env_key != NULL)
		free((*tree)->env_key);
	free(*tree);
	*tree = NULL;
}

void	free_tree(t_tree **tree)
{
	t_tree	*t_left;
	t_tree	*t_right;

	t_left = (*tree)->left;
	t_right = (*tree)->right;
	free_node(tree);
	if (t_left != NULL)
		free_tree(&t_left);
	if (t_right != NULL)
		free_tree(&t_right);
}

int	cnt_exp(char **exp)
{
	int	i;

	i = 0;
	while (exp[i])
		i++;
	return (i);
}
