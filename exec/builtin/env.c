/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:15:16 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/05 17:09:58 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_node	*is_include_env(t_env_node	**env_list, char *key)
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

int	ft_env(t_shell_info *shell)
{
	t_env_node	*list;

	list = shell->env_list;
	if (list == NULL)
		printf("super sad\n");
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (0);
}
