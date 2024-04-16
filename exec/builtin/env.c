/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:15:16 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/17 00:00:46 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_env_list(t_shell_info *shell)
{
	int	i;

	i = 0;
	if (!(shell->envp))
		return ;
	while ((shell->envp)[i])
	{
		make_env_component(&(shell->env_list), (shell->envp)[i]);
		i++;
	}
	update_env_list(&(shell->env_list), "OLDPWD", NULL);
}

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
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (CODE_SUCCESS);
}
