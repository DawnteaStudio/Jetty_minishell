/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:05:45 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/12 09:47:13 by sewopark         ###   ########.fr       */
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
	return (CODE_ERROR);
}

int	ft_cd_only(t_shell_info *shell)
{
	t_env_node	*check;
	char		*home;

	home = NULL;
	check = is_include_env(&(shell->env_list), "HOME");
	if (check)
		home = check->value;
	if (!home)
		return (ft_cd_err(NULL, 1));
	check = is_include_env(&(shell->env_list), "PWD");
	if (check)
		update_env_list(&(shell->env_list), "OLDPWD", check->value);
	else
		update_env_list(&(shell->env_list), "OLDPWD", shell->backup_pwd);
	if (chdir(home) == CODE_SUCCESS)
	{
		if (check)
			update_env_list(&(shell->env_list), "PWD", home);
		else
		{
			free(shell->backup_pwd);
			shell->backup_pwd = ft_strdup(home);
		}
		return (CODE_SUCCESS);
	}
	return (ft_cd_err(home, 0));
}

int	ft_cd(t_shell_info *shell)
{
	t_env_node	*check_pwd;
	t_env_node	*check_oldpwd;

	if (shell->tree->exp[1] == NULL)
		return (ft_cd_only(shell));
	if (chdir(shell->tree->exp[1]) != CODE_SUCCESS)
		return (ft_cd_err(shell->tree->exp[1], 0));
	check_pwd = is_include_env(&(shell->env_list), "PWD");
	check_oldpwd = is_include_env(&(shell->env_list), "OLDPWD");
	if (check_pwd)
	{
		if (check_oldpwd)
		{
			
		}
		else if (shell->oldpwd == 1)
		{
			
		}
		else
		{
			
		}
	}
		update_env_list(&(shell->env_list), "OLDPWD", check->value);
	else
		update_env_list(&(shell->env_list), "OLDPWD", shell->backup_pwd);
	return (ft_change_pwd(shell));
}
