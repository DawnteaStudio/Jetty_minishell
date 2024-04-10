/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:32:53 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/10 09:58:46 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	include_slash_case(t_shell_info *shell, char *str)
{
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) == 0)
		{
			if (execve(str, shell->d_array, shell->envp) == -1)
				exit(1);
		}
		// error_handler(PERCOMD, target.arr_cmd[0]);
	}
	// error_handler(CMDNFND, target.arr_cmd[0]);
}

void	no_include_slash_case(t_shell_info *shell, char *str, char **path)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (path[i])
	{
		tmp2 = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp2, str);
		free(tmp2);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) == 0)
				if (execve(tmp, shell->d_array, shell->envp) == -1)
					exit(2);
			// error_handler(PERCOMD, target.arr_cmd[0]);
		}
		free(tmp);
		i++;
	}
	// error_handler(CMDNFND, target.arr_cmd[0]);
}

void	ft_exec_child(t_shell_info *shell, char *str)
{
	int		i;
	char	**path;

	path = ft_get_all_path(shell);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			include_slash_case(shell, str);
		i++;
	}
	no_include_slash_case(shell, str, path);
}

int	ft_exec_node(t_shell_info *shell, char *str)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		set_signal(DEFAULT, DEFAULT);
		ft_exec_child(shell, str);
	}
	waitpid(pid, NULL, 0);
	set_signal(CUSTOM, IGNORE);
	return (0);
}
