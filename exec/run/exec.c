/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:49 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/14 10:16:51 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec_cmd(t_shell_info *shell, t_tree *tree)
{
	int	builtin;
	int	status;

	builtin = is_builtin(tree->cmd);
	if (builtin != FALSE)
	{
		status = ft_exec_builtin(shell, builtin);
		ft_restore_fd(shell);
		return (status);
	}
	else
		ft_exec_node(shell, tree);
	return (0);
}

void	ft_exec_pipe_node(t_shell_info *s, t_tree *tree, int fd[2], int dir)
{
	int	status;

	if (dir == DIRLEFT)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	status = ft_exec(s, tree);
	clean_all(s);
	exit(status);
}

int	ft_exec_pipe(t_shell_info *shell, t_tree *tree)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		fd[2];
	int		status;

	pipe(fd);
	pid_left = fork();
	if (!pid_left)
		ft_exec_pipe_node(shell, tree->left, fd, DIRLEFT);
	else
	{
		pid_right = fork();
		if (!pid_right)
			ft_exec_pipe_node(shell, tree->right, fd, DIRRIGT);
		else
		{
			ft_close_and_wait(status, fd, pid_left, pid_right);
			return (ft_exit_status(status));
		}
	}
	return (CODE_ERROR);
}

int	ft_exec(t_shell_info *shell, t_tree *tree)
{
	if (tree->type == TREE_TYPE_PIPE && tree->right)
		return (ft_exec_pipe(shell, tree));
	else if (tree->type == TREE_TYPE_PHRASE)
	{
		if (tree->left)
			return (ft_exec(shell, tree->left));
		if (tree->right)
			return (ft_exec(shell, tree->right));
	}
	else if (tree->type == TREE_TYPE_REDIRECTIONS)
	{
		if (tree->left)
			return (ft_exec(shell, tree->left));
		if (tree->right)
			return (ft_exec(shell, tree->right));
	}
	else if (tree->type == TREE_TYPE_REDIRECTION)
		return (ft_exec_redirection(tree));
	else if (tree->type == TREE_TYPE_COMMAND)
		return (ft_exec_cmd(shell, tree));
	return (ft_exec(shell, tree->left));
}
