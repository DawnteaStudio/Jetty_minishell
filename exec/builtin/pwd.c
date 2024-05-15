/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:58:07 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/14 14:04:58 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwds_helper(t_shell_info *shell, char *key)
{
	if (ft_strcmp("PWD", key) == CODE_SUCCESS)
	{
		if (shell->backup_pwd)
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
	if (node)
	{
		if (node->value)
			shell->backup_oldpwd = heap_handler(ft_strdup(node->value));
		else
			shell->backup_oldpwd = heap_handler(ft_strdup(""));
	}
	else if (str != NULL)
		shell->backup_oldpwd = heap_handler(ft_strdup(str));
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
	{
		ft_putstr_fd("jetty: can't move\n", 2);
		chdir("/Users");
		return (ERR_NOFILE);
	}
	check = is_include_env(&(shell->env_list), "PWD");
	if (check)
	{
		ft_update_oldpwd(shell, check, NULL);
		update_env_list(&(shell->env_list), "PWD", cwd);
	}
	else
		ft_update_oldpwd(shell, NULL, shell->backup_pwd);
	if (cwd)
	{
		shell->backup_pwd = heap_handler(ft_strdup(cwd));
		del(&cwd);
	}
	shell->pure_oldpwd = FALSE;
	return (CODE_SUCCESS);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("jetty: The current path has been deleted\n", 2);
		return (CODE_ERROR);
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		del(&pwd);
	}
	return (CODE_SUCCESS);
}
