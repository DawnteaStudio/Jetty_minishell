/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:02:59 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/14 14:05:36 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd_nofile(t_shell_info *shell)
{
	t_env_node	*check_pwd;
	t_env_node	*check_oldpwd;

	if (shell->pure_oldpwd == TRUE)
		shell->pure_oldpwd = FALSE;
	check_pwd = is_include_env(&(shell->env_list), "PWD");
	check_oldpwd = is_include_env(&(shell->env_list), "OLDPWD");
	if (check_oldpwd)
	{
		if (check_pwd)
			update_env_list(&(shell->env_list), "OLDPWD", check_pwd->value);
		else
			update_env_list(&(shell->env_list), "OLDPWD", shell->backup_pwd);
	}
	if (check_pwd)
		update_env_list(&(shell->env_list), "PWD", "/Users");
	else
		shell->backup_pwd = heap_handler(ft_strdup("/Users"));
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	else if (!ft_strcmp(cmd, "echo"))
		return (BLT_ECHO);
	else if (!ft_strcmp(cmd, "cd"))
		return (BLT_CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (BLT_PWD);
	else if (!ft_strcmp(cmd, "export"))
		return (BLT_EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (BLT_UNSET);
	else if (!ft_strcmp(cmd, "env"))
		return (BLT_ENV);
	else if (!ft_strcmp(cmd, "exit"))
		return (BLT_EXIT);
	else if (!ft_strcmp(cmd, ""))
		return (BLT_NULL);
	else
		return (FALSE);
}

int	ft_exec_builtin(t_shell_info *shell, t_tree *tree, int builtin)
{
	if (builtin == BLT_PWD)
		return (ft_pwd());
	else if (builtin == BLT_ENV)
		return (ft_env(shell));
	else if (builtin == BLT_ECHO)
		return (ft_echo(tree));
	else if (builtin == BLT_UNSET)
		return (ft_unset(shell, tree));
	else if (builtin == BLT_EXPORT)
		return (ft_export(shell, tree));
	else if (builtin == BLT_CD)
	{
		if (ft_cd(shell, tree) == ERR_NOFILE)
		{
			cd_nofile(shell);
			return (CODE_ERROR);
		}
		else
			return (CODE_SUCCESS);
	}
	else if (builtin == BLT_NULL)
		return (ft_null(shell, tree));
	return (ft_exit(shell, tree));
}
