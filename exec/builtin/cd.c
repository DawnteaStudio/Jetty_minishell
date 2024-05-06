/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:05:45 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/07 01:04:01 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd_err(t_shell_info *shell, char *err_msg, int home)
{
	t_env_node	*check_pwd;

	check_pwd = is_include_env(&(shell->env_list), "PWD");
	if (home)
	{
		ft_putstr_fd("jetty: cd: HOME not set\n", 2);
		return (CODE_ERROR);
	}
	if (ft_strcmp(err_msg, "") == CODE_SUCCESS)
	{
		ft_putstr_fd("\n", 1);
		if (check_pwd)
			update_env_list(&(shell->env_list), "OLDPWD", check_pwd->value);
		else
			update_env_list(&(shell->env_list), "OLDPWD", shell->backup_pwd);
		shell->pure_oldpwd = FALSE;
	}
	else
	{
		ft_putstr_fd("jetty: cd: `", 2);
		ft_putstr_fd(err_msg, 2);
		ft_putstr_fd("': No such file or directory\n", 2);
	}
	return (CODE_ERROR);
}

int	ft_cd_oldpwd(t_shell_info *shell, t_env_node *pwd, t_env_node *oldpwd)
{
	if (oldpwd && oldpwd->value)
	{
		if (chdir(oldpwd->value) == CODE_SUCCESS)
		{
			ft_putstr_fd(oldpwd->value, 1);
			ft_putstr_fd("\n", 1);
			if (pwd)
				update_env_list(&(shell->env_list), "OLDPWD", pwd->value);
			else
				update_env_list(&(shell->env_list), \
				"OLDPWD", shell->backup_pwd);
			shell->pure_oldpwd = FALSE;
			return (ft_change_pwd(shell));
		}
		ft_cd_err(shell, oldpwd->value, 0);
	}
	else
		ft_putstr_fd("jetty: cd: OLDPWD not set\n", 2);
	return (CODE_ERROR);
}

int	ft_cd_home_env_update(t_shell_info *shell, char *home)
{
	t_env_node	*check_pwd;
	t_env_node	*check_oldpwd;

	check_pwd = is_include_env(&(shell->env_list), "PWD");
	check_oldpwd = is_include_env(&(shell->env_list), "OLDPWD");
	if (chdir(home) == CODE_SUCCESS)
	{
		if (check_oldpwd)
		{
			if (check_pwd)
				update_env_list(&(shell->env_list), "OLDPWD", check_pwd->value);
			else
				update_env_list(&(shell->env_list), \
				"OLDPWD", shell->backup_pwd);
		}
		return (ft_change_pwd(shell));
	}
	return (CODE_ERROR);
}

int	ft_cd_home(t_shell_info *shell)
{
	t_env_node	*check;
	char		*home;
	int			status;

	home = NULL;
	check = is_include_env(&(shell->env_list), "HOME");
	if (check)
		home = check->value;
	if (!home)
		return (ft_cd_err(shell, NULL, 1));
	status = ft_cd_home_env_update(shell, home);
	if (status == CODE_SUCCESS)
	{
		shell->pure_oldpwd = FALSE;
		return (CODE_SUCCESS);
	}
	return (ft_cd_err(shell, home, 0));
}

int	ft_cd(t_shell_info *shell, t_tree *tree)
{
	t_env_node	*check_pwd;
	t_env_node	*check_oldpwd;

	if (shell->pure_oldpwd == TRUE)
		shell->pure_oldpwd = FALSE;
	check_pwd = is_include_env(&(shell->env_list), "PWD");
	check_oldpwd = is_include_env(&(shell->env_list), "OLDPWD");
	if (tree->exp[1] == NULL || ft_strcmp(tree->exp[1], "~") == CODE_SUCCESS)
		return (ft_cd_home(shell));
	else if (ft_strcmp(tree->exp[1], "-") == CODE_SUCCESS)
		return (ft_cd_oldpwd(shell, check_pwd, check_oldpwd));
	if (chdir(tree->exp[1]) != CODE_SUCCESS)
		return (ft_cd_err(shell, tree->exp[1], 0));
	if (check_oldpwd)
	{
		if (check_pwd)
			update_env_list(&(shell->env_list), "OLDPWD", check_pwd->value);
		else
			update_env_list(&(shell->env_list), "OLDPWD", shell->backup_pwd);
	}
	return (ft_change_pwd(shell));
}
