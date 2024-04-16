/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:06:51 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/17 00:13:54 by parksewon        ###   ########.fr       */
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

void	add_env_value_back(t_component *cp, char *env_line)
{
	char	*tmp;

	tmp = NULL;
	if (cp->i < cp->len)
		cp->value = heap_handler(ft_substr(env_line, cp->i, cp->len - 1));
	else if (cp->i == cp->len)
		cp->value = heap_handler(ft_strdup(""));
	if (cp->check)
	{
		if (cp->check->value == NULL)
			update_env_list(cp->new_env_list, cp->key, cp->value);
		else
		{
			tmp = ft_strdup(cp->check->value);
			cp->check->value = heap_handler(ft_strjoin(tmp, cp->value));
			del(tmp);
		}
	}
	else
		update_env_list(cp->new_env_list, cp->key, cp->value);
}

void	make_env_component_checker(t_component *cp, char *env_line)
{
	while (env_line[cp->i])
	{
		if (env_line[cp->i] == '=')
		{
			cp->key = heap_handler(ft_substr(env_line, 0, cp->i++));
			cp->flag_check_value = TRUE;
			return ;
		}
		else if (env_line[cp->i] == '+' && cp->i + 1 < cp->len)
		{
			if (env_line[cp->i + 1] == '=')
			{
				cp->key = heap_handler(ft_substr(env_line, 0, cp->i));
				cp->flag_check_value = ADDBACK;
				cp->check = is_include_env(cp->new_env_list, cp->key);
				cp->i += 2;
				add_env_value_back(cp, env_line);
				return ;
			}
		}
		cp->i++;
	}
}

void	make_env_component(t_env_node **new_env_list, char *env_line)
{
	t_component	cp;

	ft_memset(&cp, 0, sizeof(t_component));
	cp.len = ft_strlen(env_line);
	cp.new_env_list = new_env_list;
	make_env_component_checker(&cp, env_line);
	if (cp.flag_check_value == TRUE)
	{
		if (cp.i < cp.len)
			cp.value = heap_handler(ft_substr(env_line, cp.i, cp.len - 1));
		else if (cp.i == cp.len)
			cp.value = heap_handler(ft_strdup(""));
		update_env_list(new_env_list, cp.key, cp.value);
	}
	else if (cp.flag_check_value == FALSE)
	{
		cp.key = heap_handler(ft_substr(env_line, 0, cp.len));
		cp.check = is_include_env(new_env_list, cp.key);
		if (cp.check == NULL)
			update_env_list(new_env_list, cp.key, cp.value);
	}
}
