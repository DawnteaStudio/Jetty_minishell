/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:32:53 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/06 20:14:41 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_new_envp(t_shell_info *shell)
{
	int			i;
	t_env_node	*list;

	i = 0;
	list = shell->env_list;
	shell->env = (char **)malloc(sizeof(char *) * \
	ft_get_len(shell->env_list) + 1);
	if (shell->env == NULL)
		ft_error(MEMORY);
	update_env_list(&(shell->env_list), "PWD", shell->backup_pocket->pwd);
	update_env_list(&(shell->env_list), "SHLVL", shell->backup_pocket->shlvl);
	make_new_envp_helper(shell, list, &i);
	shell->env[i] = NULL;
}

void	include_slash_case(t_shell_info *shell, t_tree *tree)
{
	make_new_envp(shell);
	if (access(tree->cmd, F_OK) == 0)
	{
		if (access(tree->cmd, X_OK) == 0)
		{
			if (execve(tree->cmd, tree->exp, shell->env) == -1)
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
	make_new_envp(shell);
	while (path[i])
	{
		tmp2 = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp2, tree->cmd);
		del(&tmp2);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) == 0)
			{
				if (execve(tmp, tree->exp, shell->env) == -1)
					exit(putstr_error(tree->cmd, CODE_ERROR, ERR_PERROR));
			}
			exit(putstr_error(tree->cmd, CODE_NOT_EXEC, ERR_PER_DENIED));
		}
		del(&tmp);
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
	ignore_white_node(shell, tree);
	while (tree->cmd[i])
	{
		if (tree->cmd[i] == '/')
			include_slash_case(shell, tree);
		i++;
	}
	if (path)
		no_include_slash_case(shell, tree, path);
	else
		include_slash_case(shell, tree);
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
	ft_restore_fd(shell, 0);
	return (ft_exit_status(status));
}
