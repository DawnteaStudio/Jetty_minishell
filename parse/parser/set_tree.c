/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:48:27 by erho              #+#    #+#             */
/*   Updated: 2024/05/05 14:36:05 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**extract_data(char *str, char *cmd, t_env_node **env_list)
{
	t_syntax	st;
	char		*temp;
	char		**res;

	res = set_exp();
	ft_memset(&st, 0, sizeof(t_syntax));
	st.sample = cmd;
	while (str[st.width])
	{
		st.len = 0;
		st.q_back_up = st.quotes;
		tree_find_idx(str, &st);
		temp = (char *)malloc(sizeof(char) * (st.len + 1));
		if (temp == NULL)
			exit(1);
		tree_make_word(temp, &str[st.word], st);
		res = join_exp_n_str(res, &temp);
		st.height++;
		if (str[st.width])
			res = get_env_value(env_list, str, res, &st);
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
	new_node->origin_token = NULL;
	new_node->here_doc = -1;
	new_node->tmp_file = NULL;
	return (new_node);
}
