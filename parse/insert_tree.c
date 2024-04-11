/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:05:09 by erho              #+#    #+#             */
/*   Updated: 2024/04/12 02:09:11 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	join_exp(t_tree **tree, char *str, t_env_node **env_list)
{
	int		cnt;
	int		i;
	char	**tmp;

	cnt = cnt_exp((*tree)->exp) + 1;
	tmp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (tmp == NULL)
		exit(1);
	tmp[cnt] = NULL;
	i = 0;
	while ((*tree)->exp[i])
	{
		tmp[i] = (*tree)->exp[i];
		i++;
	}
	tmp[i] = extract_data(str, env_list);
	free((*tree)->exp);
	(*tree)->exp = tmp;
}

void	command_node(t_tree **tree, t_token *tokens, t_env_node **env_list,
		int *idx)
{
	t_tree	*new_node;

	if ((*tree)->right == NULL)
		(*tree)->right = create_node(TREE_TYPE_COMMAND);
	new_node = (*tree)->right;
	if (new_node->cmd == NULL)
	{
		new_node->cmd = extract_data(tokens[*idx].str, env_list);
		(*idx)++;
	}
	while (tokens[*idx].type == TOKEN_TYPE_WORD)
	{
		if (new_node->exp == NULL)
		{
			new_node->exp = (char **)malloc(sizeof(char *) * 2);
			new_node->exp[0] = extract_data(tokens[*idx].str, env_list);
			new_node->exp[1] = NULL;
		}
		else
			join_exp(&new_node, tokens[*idx].str, env_list);
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
		return (CODE_ERROR);
	new_node->redir_info = extract_data(tokens[*idx].str, env_list);
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
