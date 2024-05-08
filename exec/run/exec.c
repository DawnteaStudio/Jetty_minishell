/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:49 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/09 00:44:58 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec_cmd(t_shell_info *shell, t_tree *tree, t_tree *redirs, int piped)
{
	int	builtin;
	int	status;

	if (tree != NULL)
	{
		builtin = is_builtin(tree->cmd);
		if (builtin != FALSE)
		{
			status = ft_add_redirection(redirs);
			if (status == CODE_ERROR)
				return (ft_restore_fd(shell, status));
			status = ft_exec_builtin(shell, tree, builtin);
			return (ft_restore_fd(shell, status));
		}
		status = ft_add_redirection(redirs);
		if (status == CODE_ERROR)
			return (ft_restore_fd(shell, status));
		return (ft_exec_node(shell, tree, piped));
	}
	else
		status = ft_add_redirection(redirs);
	return (ft_restore_fd(shell, status));
}

void	ft_exec_pipe_node(t_shell_info *s, t_tree *tree, int fd[2], int dir)
{
	int	status;

	s->origin = FALSE;
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
	status = ft_exec(s, tree, TRUE);
	clean_all(s);
	exit(status);
}

int	ft_exec_pipe(t_shell_info *shell, t_tree *tree, int piped)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		fd[2];
	int		status;

	pipe(fd);
	pid_left = fork();
	set_signal(DEFAULT, DEFAULT);
	if (!pid_left)
		ft_exec_pipe_node(shell, tree->left, fd, DIRLEFT);
	else
	{
		pid_right = fork();
		if (!pid_right)
			ft_exec_pipe_node(shell, tree->right, fd, DIRRIGT);
		else
		{
			if (shell->origin == TRUE)
				set_signal(CHSIGINT, CUSTOM);
			status = ft_close_and_wait(&status, fd, pid_right);
			return (ft_exit_status(status, piped));
		}
	}
	return (CODE_ERROR);
}

void	ft_exec_preprocess(t_shell_info *shell, t_tree *tree)
{
	t_tree	*tmp;

	tmp = tree;
	if (tmp->cmd && ft_strcmp(tmp->cmd, "export") == CODE_SUCCESS)
	{
		if (tmp->exp[1] == NULL)
			ft_check_backup_pwd(shell);
	}
	else if (tmp->type == TREE_TYPE_REDIRECTIONS)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->left->redir, "<<") == CODE_SUCCESS)
				ft_here_doc(shell, tmp->left);
			else
				break ;
			tmp = tmp->right;
		}
	}
	if (tmp && tmp->left)
		ft_exec_preprocess(shell, tmp->left);
	if (tmp && tmp->right)
		ft_exec_preprocess(shell, tmp->right);
}

int	ft_exec(t_shell_info *shell, t_tree *tree, int piped)
{
	if (tree->type == TREE_TYPE_PIPE && tree->right)
		return (ft_exec_pipe(shell, tree, TRUE));
	else if (tree->type == TREE_TYPE_PHRASE)
		return (ft_exec_cmd(shell, tree->right, tree->left, piped));
	return (ft_exec(shell, tree->left, piped));
}
