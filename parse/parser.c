/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:19:03 by erho              #+#    #+#             */
/*   Updated: 2024/04/21 18:54:34 by erho             ###   ########.fr       */
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
	tree = create_node(TREE_TYPE_PIPE);
	error_flag = pipe_node(&tree, tokens, env_list, 0);
	free_tokens(tokens);
	if (error_flag == CODE_ERROR)
	{
		ft_putstr_fd("jetty: syntax error near unexpected token '|'\n", 2);
		g_exit_code = 1;
		free_tree(&tree);
	}
	return (tree);
}
