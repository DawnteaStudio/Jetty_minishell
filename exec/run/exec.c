/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:49 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/16 11:05:12 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec_cmd(t_shell_info *shell, t_tree *tree, t_tree *redirs)
{
	int	builtin;
	int	status;

	while (redirs)
	{
		ft_exec_redirection(redirs->left);
		if (redirs->right)
			redirs = redirs->right;
		else
			break ;
	}
	builtin = is_builtin(tree->cmd);
	if (builtin != FALSE)
	{
		status = ft_exec_builtin(shell, tree, builtin);
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
			ft_close_and_wait(&status, fd);
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
		return (ft_exec_cmd(shell, tree->right, tree->left));
	return (ft_exec(shell, tree->left));
}
