/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:15:16 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/01 22:39:01 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_new_envp_helper(t_shell_info *shell, t_env_node *list, int *i)
{
	char	*tmp;

	while (list)
	{
		if (list->value)
		{
			tmp = ft_strjoin(list->key, "=");
			shell->env[*i] = ft_strjoin(tmp, list->value);
			del(&tmp);
		}
		else
			shell->env[*i] = ft_strdup(list->key);
		list = list->next;
		(*i)++;
	}
}

int	is_include_env_path(t_env_node *path)
{
	char	**tmp;
	int		i;

	i = 0;
	if (path->value == NULL)
		return (FALSE);
	tmp = ft_split(path->value, ':');
	while (tmp[i])
	{
		if (ft_strcmp(tmp[i], "/usr/bin") == CODE_SUCCESS)
		{
			free_split_arr(tmp);
			return (TRUE);
		}
		i++;
	}
	free_split_arr(tmp);
	return (FALSE);
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

int	ft_env(t_shell_info *shell)
{
	t_env_node	*list;
	t_env_node	*path;
	update_env_list(&(shell->env_list), "_", "/usr/bin/env");
	path = is_include_env(&(shell->env_list), "PATH");
	if (path == NULL)
	{
		if (shell->path_avil == FALSE)
			return (putstr_error("env", CODE_ERROR, ERR_NO_SUCH_FILE));
	}
	else
	{
		if (is_include_env_path(path) == FALSE)
			return (putstr_error("env", CODE_ERROR, ERR_NO_SUCH_FILE));
	}
	list = shell->env_list;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (CODE_SUCCESS);
}
