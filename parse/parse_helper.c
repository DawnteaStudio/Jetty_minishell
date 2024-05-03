/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:17:11 by erho              #+#    #+#             */
/*   Updated: 2024/05/03 19:52:05 by erho             ###   ########.fr       */
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

void	free_exp(char **exp)
{
	int	idx;

	idx = 0;
	while (exp[idx] != NULL)
	{
		free(exp[idx]);
		idx++;
	}
	free(exp[idx]);
	free(exp);
}

void	free_node(t_tree **tree)
{
	if ((*tree)->cmd != NULL)
		free((*tree)->cmd);
	if ((*tree)->redir != NULL)
		free((*tree)->redir);
	if ((*tree)->origin_token != NULL)
		free((*tree)->origin_token);
	if ((*tree)->redir_info != NULL)
		free_exp((*tree)->redir_info);
	if ((*tree)->exp != NULL)
		free_exp((*tree)->exp);
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
