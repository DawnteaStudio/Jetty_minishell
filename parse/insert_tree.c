/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:05:09 by erho              #+#    #+#             */
/*   Updated: 2024/04/25 05:50:43 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	join_exp(t_tree **tree, char *str, t_env_node **env_list)
{
	int		cnt;
	t_token	*tmp_token;
	char	**new_exp;
	char	**tmp;

	tmp_token = extract_data(str, env_list);
	tmp = set_exp(tmp_token);
	cnt = cnt_exp((*tree)->exp) + cnt_exp(tmp);
	new_exp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (new_exp == NULL)
		exit(1);
	new_exp[cnt] = NULL;
	cpy_new_exp(new_exp, (*tree)->exp, tmp);
	free((*tree)->exp);
	free_tokens(tmp_token);
	free(tmp);
	(*tree)->exp = new_exp;
}

void	command_node(t_tree **tree, t_token *tokens, t_env_node **env_list,
		int *idx)
{
	t_tree	*new_node;
	t_token	*tmp;

	if ((*tree)->right == NULL)
		(*tree)->right = create_node(TREE_TYPE_COMMAND);
	new_node = (*tree)->right;
	if (new_node->cmd == NULL)
	{
		tmp = extract_data(tokens[*idx].str, env_list);
		new_node->cmd = ft_strdup(tmp[0].str);
		new_node->exp = set_exp(tmp);
		free_tokens(tmp);
		(*idx)++;
	}
	while (tokens[*idx].type == TOKEN_TYPE_WORD)
	{
		join_exp(&new_node, tokens[*idx].str, env_list);
		(*idx)++;
	}
}

int	redirects_node(t_tree **tree, t_token *tokens, t_env_node **env_list,
		int *idx)
{
	t_tree	*new_node;
	t_token	*tmp;

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
		return (CODE_ERROR);
	tmp = extract_data(tokens[*idx].str, env_list);
	new_node->redir_info = set_exp(tmp);
	new_node->origin_token = ft_strdup(tokens[*idx].str);
	free_tokens(tmp);
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
		return (CODE_ERROR);
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
