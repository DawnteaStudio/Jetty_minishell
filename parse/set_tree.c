/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:48:27 by erho              #+#    #+#             */
/*   Updated: 2024/04/11 23:16:15 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_data(char *str, t_env_node **env_list)
{
	t_command	cmd;
	char		*temp;
	char		q_back_up;
	char		*res;

	res = (char *)malloc(sizeof(char));
	if (res == NULL)
		exit(1);
	res[0] = '\0';
	ft_memset(&cmd, 0, sizeof(t_command));
	q_back_up = '\0';
	while (str[cmd.width])
	{
		cmd.len = 0;
		tree_find_idx(str, &cmd);
		swap_ch(&cmd.quotes, &q_back_up);
		temp = (char *)malloc(sizeof(char) * (cmd.len + 1));
		if (temp == NULL)
			exit(1);
		tree_make_word(temp, &str[cmd.word], cmd);
		swap_ch(&cmd.quotes, &q_back_up);
		res = res_join(&res, &temp);
		if (str[cmd.width] != '\0')
			res = get_env_value(env_list, str, &res, &cmd);
	}
	return (res);
}

t_tree	*create_node(int type)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (new_node == NULL)
		exit(1);
	new_node->type = type;
	new_node->cmd = NULL;
	new_node->redir = NULL;
	new_node->redir_info = NULL;
	new_node->exp = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
