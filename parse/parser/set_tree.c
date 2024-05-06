/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:48:27 by erho              #+#    #+#             */
/*   Updated: 2024/05/06 18:33:45 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**extract_data(char *str, char *cmd, t_env_node **env_list)
{
	t_syntax	st;
	char		*temp;
	char		**res;

	ft_memset(&st, 0, sizeof(t_syntax));
	res = set_exp(1);
	res[0] = ft_strdup("");
	st.sample = cmd;
	while (str[st.width])
	{
		st.len = 0;
		st.q_back_up = st.quotes;
		tree_find_idx(str, &st);
		if (!(st.len == 0 && st.height != 0))
		{
			temp = (char *)malloc(sizeof(char) * (st.len + 1));
			if (temp == NULL)
				ft_error(MEMORY);
			tree_make_word(temp, &str[st.word], st);
			res = join_exp_n_str(res, temp, &st);
		}
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
		ft_error(MEMORY);
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
