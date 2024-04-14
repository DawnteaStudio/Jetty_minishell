/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:05:45 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/14 23:26:23 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd_err(char *err_msg, int home)
{
	if (home)
	{
		ft_putstr_fd("jetty: cd: HOME not set\n", 2);
		return (CODE_ERROR);
	}
	ft_putstr_fd("jetty: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (CODE_ERROR);
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
		update_env_list(&(shell->env_list), "PWD", cwd);
	else
	{
		free(shell->backup_pwd);
		shell->backup_pwd = ft_strdup(cwd);
	}
	free(cwd);
	return (CODE_SUCCESS);
}

int	ft_cd_only_env_update(t_shell_info *shell, char *home)
{
	t_env_node	*check_pwd;
	t_env_node	*check_oldpwd;

	check_pwd = is_include_env(&(shell->env_list), "PWD");
	check_oldpwd = is_include_env(&(shell->env_list), "OLDPWD");
	if (check_oldpwd)
	{
		if (check_pwd)
			update_env_list(&(shell->env_list), "OLDPWD", check_pwd->value);
		else if (shell->unset_pwd == 1)
		{
			shell->unset_pwd = 0;
			update_env_list(&(shell->env_list), "OLDPWD", "");
		}
		else
			update_env_list(&(shell->env_list), "OLDPWD", shell->backup_pwd);
	}
	if (chdir(home) == CODE_SUCCESS)
	{
		if (check_pwd)
			update_env_list(&(shell->env_list), "PWD", home);
		return (CODE_SUCCESS);
	}
	return (CODE_ERROR);
}

int	ft_cd_only(t_shell_info *shell)
{
	t_env_node	*check;
	char		*home;
	int			status;

	home = NULL;
	check = is_include_env(&(shell->env_list), "HOME");
	if (check)
		home = check->value;
	if (!home)
		return (ft_cd_err(NULL, 1));
	status = ft_cd_only_env_update(shell, home);
	if (status == CODE_SUCCESS)
		return (CODE_SUCCESS);
	return (ft_cd_err(home, 0));
}

int	ft_cd(t_shell_info *shell, t_tree *tree)
{
	t_env_node	*check_pwd;
	t_env_node	*check_oldpwd;

	if (tree->exp[1] == NULL)
		return (ft_cd_only(shell));
	if (chdir(tree->exp[1]) != CODE_SUCCESS)
		return (ft_cd_err(tree->exp[1], 0));
	check_pwd = is_include_env(&(shell->env_list), "PWD");
	check_oldpwd = is_include_env(&(shell->env_list), "OLDPWD");
	if (check_oldpwd)
	{
		if (check_pwd)
			update_env_list(&(shell->env_list), "OLDPWD", check_pwd->value);
		else if (shell->unset_pwd == 1)
		{
			shell->unset_pwd = 0;
			update_env_list(&(shell->env_list), "OLDPWD", "");
		}
		else
			update_env_list(&(shell->env_list), "OLDPWD", shell->backup_pwd);
	}
	return (ft_change_pwd(shell));
}
