/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:58:07 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/17 00:11:27 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
