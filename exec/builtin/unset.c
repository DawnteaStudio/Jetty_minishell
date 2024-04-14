/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:20:24 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/14 16:40:00 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (TRUE);
	else if (c == '_')
		return (TRUE);
	return (FALSE);
}

int	is_valid_key(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') \
	|| str[i] == '_')
	{
		while (str[i] && str[i] != '=')
		{
			if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

void	unset(t_shell_info *shell, char *key)
{
	t_env_node	*cur;
	t_env_node	*pre;

	pre = NULL;
	cur = shell->env_list;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == CODE_SUCCESS)
		{
			if (pre)
				pre->next = cur->next;
			else
				shell->env_list = cur->next;
			if (ft_strcmp("PWD", key)== CODE_SUCCESS)
				shell->unset_pwd = 1;
			free(cur);
			return ;
		}
		pre = cur;
		cur = cur->next;
	}
}

int	ft_unset(t_shell_info *shell, t_tree *tree)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = CODE_SUCCESS;
	while (tree->exp[i])
	{
		if (is_valid_key(tree->exp[i]) == FALSE)
		{
			ft_putstr_fd("jetty: unset: `", 2);
			ft_putstr_fd(tree->exp[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_code = CODE_ERROR;
		}
		else
			unset(shell, tree->exp[i]);
		i++;
	}
	return (exit_code);
}
