/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test_env_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:32:28 by erho              #+#    #+#             */
/*   Updated: 2024/04/12 01:02:38 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_node	*create_list(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = (t_env_node *)malloc(sizeof(t_env_node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env_node	*is_include_env(t_env_node **env_list, char *key)
{
	t_env_node	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}