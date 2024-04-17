/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:32:53 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/17 21:03:17 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	include_slash_case(t_shell_info *shell, t_tree *tree)
{
	if (access(tree->cmd, F_OK) == 0)
	{
		if (access(tree->cmd, X_OK) == 0)
		{
			if (execve(tree->cmd, shell->tree->exp, shell->envp) == -1)
				exit(putstr_error(tree->cmd, CODE_ERROR, ERR_PERROR));
		}
		exit(putstr_error(tree->cmd, CODE_NOT_EXEC, ERR_PER_DENIED));
	}
	exit(putstr_error(tree->cmd, CODE_NOT_FOUND, ERR_NO_SUCH_FILE));
}

void	no_include_slash_case(t_shell_info *shell, t_tree *tree, char **path)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (path[i])
	{
		tmp2 = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp2, tree->cmd);
		del(tmp2);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) == 0)
			{
				printf("%s\n", tmp);
				if (execve(tmp, tree->exp, shell->envp) == -1)
					exit(putstr_error(tree->cmd, CODE_ERROR, ERR_PERROR));
			}
			exit(putstr_error(tree->cmd, CODE_NOT_EXEC, ERR_PER_DENIED));
		}
		del(tmp);
		i++;
	}
	exit(putstr_error(tree->cmd, CODE_NOT_FOUND, ERR_CMD_NOT_FND));
}

void	ft_exec_child(t_shell_info *shell, t_tree *tree)
{
	int		i;
	char	**path;

	path = ft_get_all_path(shell);
	i = 0;
	printf("i'm here exec_child\n");
	while (tree->cmd[i])
	{
		if (tree->cmd[i] == '/')
			include_slash_case(shell, tree);
		i++;
	}
	no_include_slash_case(shell, tree, path);
}

int	ft_exec_node(t_shell_info *shell, t_tree *tree)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
		ft_exec_child(shell, tree);
	waitpid(pid, &status, 0);
	return (ft_exit_status(status));
}
