/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:05:09 by erho              #+#    #+#             */
/*   Updated: 2024/05/07 00:29:49 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_error(int flag, t_token tokens)
{
	ft_putstr_fd("jetty: syntax error near unexpected token ", 2);
	if (tokens.type == TOKEN_TYPE_NULL)
		ft_putstr_fd("'newline'\n", 2);
	else
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(tokens.str, 2);
		ft_putstr_fd("'\n", 2);
	}
	g_exit_code = 258;
	return (flag);
}

void	command_node(t_tree **tree, t_token *tokens, t_env_node **env_list,
		int *idx)
{
	t_tree	*new_node;
	char	**tmp;
	char	**exp;

	if ((*tree)->right == NULL)
		(*tree)->right = create_node(TREE_TYPE_COMMAND);
	new_node = (*tree)->right;
	if (new_node->cmd == NULL)
	{
		exp = extract_data(tokens[*idx].str, "", env_list);
		new_node->cmd = ft_strdup(exp[0]);
		new_node->exp = exp;
		(*idx)++;
	}
	while (tokens[*idx].type == TOKEN_TYPE_WORD)
	{
		tmp = extract_data(tokens[*idx].str, new_node->cmd, env_list);
		new_node->exp = join_exp(new_node->exp, tmp, cnt_exp(new_node->exp));
		(*idx)++;
	}
}

int	redirects_node(t_tree **tree, t_token *tokens, t_env_node **env_list,
		int *idx)
{
	t_tree	*new_node;

	if ((*tree)->left == NULL)
	{
		(*tree)->left = create_node(TREE_TYPE_REDIRECTIONS);
		new_node = (*tree)->left;
	}
	else
	{
		new_node = find_last_right((*tree)->left);
		new_node->right = create_node(TREE_TYPE_REDIRECTIONS);
		new_node = new_node->right;
	}
	new_node->left = create_node(TREE_TYPE_REDIRECTION);
	new_node = new_node->left;
	new_node->redir = ft_strdup(tokens[*idx].str);
	(*idx)++;
	if (tokens[*idx].type != TOKEN_TYPE_WORD)
		return (redir_error(CODE_ERROR, tokens[*idx]));
	new_node->redir_info = extract_data(tokens[*idx].str,
			new_node->redir, env_list);
	new_node->origin_token = ft_strdup(tokens[*idx].str);
	(*idx)++;
	return (CODE_SUCCESS);
}

int	phrase_node(t_tree **tree, t_token *tokens, t_env_node **env_list,
		int idx)
{
	while (tokens[idx].str && tokens[idx].type != TOKEN_TYPE_PIPE)
	{
		if (tokens[idx].type == TOKEN_TYPE_REDIRECTION)
		{
			if (redirects_node(tree, tokens, env_list, &idx) == CODE_ERROR)
				return (CODE_ERROR);
		}
		else
			command_node(tree, tokens, env_list, &idx);
	}
	return (CODE_SUCCESS);
}

int	pipe_node(t_tree **tree, t_token *tokens, t_env_node **env_list, int idx)
{
	int	start;

	start = idx;
	while (tokens[idx].str && tokens[idx].type != TOKEN_TYPE_PIPE)
		idx++;
	if (start == idx)
	{
		ft_putstr_fd("jetty: syntax error near unexpected token '|'\n", 2);
		g_exit_code = 258;
		return (CODE_ERROR);
	}
	(*tree)->left = create_node(TREE_TYPE_PHRASE);
	if (phrase_node(&((*tree)->left), tokens, env_list, start) == CODE_ERROR)
		return (CODE_ERROR);
	if (tokens[idx].str != NULL)
	{
		(*tree)->right = create_node(TREE_TYPE_PIPE);
		if (pipe_node(&((*tree)->right), tokens, env_list, idx + 1)
			== CODE_ERROR)
			return (CODE_ERROR);
	}
	return (CODE_SUCCESS);
}
