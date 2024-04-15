/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:48:27 by erho              #+#    #+#             */
/*   Updated: 2024/04/16 01:10:06 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_data(char *str, t_env_node **env_list, t_tree	**tree)
{
	t_command	cmd;
	char		*temp;
	char		*res;
	char		*value;

	res = ft_strdup("");
	ft_memset(&cmd, 0, sizeof(t_command));
	while (str[cmd.width])
	{
		cmd.len = 0;
		tree_find_idx(str, &cmd);
		swap_ch(&cmd.quotes, &cmd.q_back_up);
		temp = (char *)malloc(sizeof(char) * (cmd.len + 1));
		if (temp == NULL)
			exit(1);
		tree_make_word(temp, &str[cmd.word], cmd);
		swap_ch(&cmd.quotes, &cmd.q_back_up);
		res = res_join(&res, &temp);
		if (str[cmd.width] != '\0')
		{
			value = check_key(env_list, str, &cmd, tree);
			res = get_env_value(&value, str, &res, &cmd);
		}
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
	new_node->is_env = FALSE;
	new_node->env_key = NULL;
	return (new_node);
}
