/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:21:18 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/16 23:24:40 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_print_export_error(char *str)
{
	ft_putstr_fd("jetty: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (CODE_ERROR);
}

void	ft_check_backup_pwd(t_shell_info *shell)
{
	t_env_node	*check_pwd;
	t_env_node	*check_oldpwd;

	check_pwd = is_include_env(&(shell->env_list), "PWD");
	check_oldpwd = is_include_env(&(shell->env_list), "OLDPWD");
	if (check_pwd && check_pwd->value)
		return ;
	if (check_oldpwd)
	{
		if (shell->backup_pwd == NULL)
			shell->backup_pwd = ft_strdup("");
	}
}

void	ft_print_export_list(t_shell_info *shell)
{
	t_env_node	*list;
	int			i;

	list = shell->env_list;
	while (list)
	{
		i = 0;
		if (list->value && (ft_strcmp(list->key, "_") != 0))
		{
			printf("declare -x %s=\"", list->key);
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					printf("\\%c", (list->value)[i++]);
				else
					printf("%c", (list->value)[i++]);
			}
			printf("\"\n");
		}
		else if (!(ft_strcmp(list->key, "OLDPWD") || shell->pure_oldpwd))
			printf("declare -x %s=\"\"\n", list->key);
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

void	ft_restore_pwd(t_shell_info *shell, t_tree *tree, int i)
{
	if (ft_strcmp("PWD", tree->exp[i]) == CODE_SUCCESS)
	{
		if (is_include_env(&(shell->env_list), "PWD")->value == NULL)
			update_env_list(&(shell->env_list), "PWD", shell->backup_pwd);
	}
	else if (ft_strcmp("OLDPWD", tree->exp[i]) == CODE_SUCCESS)
	{
		if (is_include_env(&(shell->env_list), "OLDPWD") == NULL)
			shell->pure_oldpwd = TRUE;
	}
}

int	ft_export(t_shell_info *shell, t_tree *tree)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = CODE_SUCCESS;
	if (tree->exp[1] == NULL)
		ft_print_export_list(shell);
	else
	{
		while (tree->exp[i])
		{
			if (is_valid_key(tree->exp[i]) == FALSE)
				exit_code = ft_print_export_error(tree->exp[i]);
			else
				make_env_component(&(shell->env_list), tree->exp[i]);
			ft_restore_pwd(shell, tree, i);
			i++;
		}
	}
	return (exit_code);
}
