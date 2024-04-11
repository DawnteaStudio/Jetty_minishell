/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:19:03 by erho              #+#    #+#             */
/*   Updated: 2024/04/12 01:22:55 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*parse(char *str, t_env_node **env_list)
{
	t_token	*tokens;
	t_tree	*tree;
	int		error_flag;

	tokens = lexical_analyze(str);
	if (tokens == NULL)
		return (NULL);
	tree = create_node(TREE_TYPE_HEAD);
	error_flag = pipe_node(&tree, tokens, env_list, 0);
	free_tokens(tokens);
	if (error_flag == CODE_ERROR)
		free_tree(&tree);
	return (tree);
}
