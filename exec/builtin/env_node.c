/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:06:51 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/16 22:06:03 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_node	*ft_env_node_new(char *key, char *value)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (!node)
		return (NULL);
	node->key = heap_handler(ft_strdup(key));
	if (value)
		node->value = heap_handler(ft_strdup(value));
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	update_env_list(t_env_node	**env_list, char *key, char *value)
{
	t_env_node	*check;
	t_env_node	*cur;

	check = is_include_env(env_list, key);
	if (check)
	{
		if (value)
			check->value = heap_handler(ft_strdup(value));
		else
			check->value = NULL;
	}
	else
	{
		if (*env_list == NULL)
			*env_list = ft_env_node_new(key, value);
		else
		{
			cur = *env_list;
			while (cur && cur->next)
				cur = cur->next;
			cur->next = ft_env_node_new(key, value);
		}
	}
}

void	make_env_component(t_env_node **new_env_list, char *env_line)
{
	t_component	cp;

	ft_memset(&cp, 0, sizeof(t_component));
	cp.len = ft_strlen(env_line);
	while (env_line[cp.i])
	{
		if (env_line[cp.i] == '=')
		{
			cp.key = heap_handler(ft_substr(env_line, 0, cp.i++));
			cp.flag_check_value = TRUE;
			break ;
		}
		cp.i++;
	}
	if (cp.flag_check_value == TRUE && cp.i < cp.len)
		cp.value = heap_handler(ft_substr(env_line, cp.i, cp.len - 1));
	else if (cp.flag_check_value == FALSE && cp.key == NULL)
		cp.key = heap_handler(ft_substr(env_line, 0, cp.len));
	update_env_list(new_env_list, cp.key, cp.value);
}

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
