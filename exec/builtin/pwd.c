/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:58:07 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/25 03:55:50 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwds_helper(t_shell_info *shell, char *key)
{
	if (ft_strcmp("PWD", key) == CODE_SUCCESS)
	{
		if (shell->backup_pwd)
			del(shell->backup_pwd);
		shell->backup_pwd = NULL;
	}
	else if (ft_strcmp("OLDPWD", key) == CODE_SUCCESS)
	{
		shell->cd_before = FALSE;
		shell->pure_oldpwd = TRUE;
	}
	else if (ft_strcmp("PATH", key) == CODE_SUCCESS)
		shell->path_avil = FALSE;
}

void	ft_update_oldpwd(t_shell_info *shell, t_env_node *node, char *str)
{
	if (shell->backup_oldpwd)
		del(shell->backup_oldpwd);
	if (node)
	{
		if (node->value)
			shell->backup_oldpwd = ft_strdup(node->value);
		else
			shell->backup_oldpwd = ft_strdup("");
	}
	else if (str != NULL)
		shell->backup_oldpwd = ft_strdup(str);
	else
	{
		shell->backup_oldpwd = NULL;
		shell->cd_before = TRUE;
	}
}

int	ft_change_pwd(t_shell_info *shell)
{
	t_env_node	*check;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (CODE_ERROR);
	check = is_include_env(&(shell->env_list), "PWD");
	if (check)
	{
		ft_update_oldpwd(shell, check, NULL);
		update_env_list(&(shell->env_list), "PWD", cwd);
	}
	else
	{
		ft_update_oldpwd(shell, NULL, shell->backup_pwd);
		if (shell->backup_pwd)
			del(shell->backup_pwd);
		shell->backup_pwd = ft_strdup(cwd);
	}
	del(cwd);
	shell->pure_oldpwd = FALSE;
	return (CODE_SUCCESS);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	del(pwd);
	return (CODE_SUCCESS);
}
