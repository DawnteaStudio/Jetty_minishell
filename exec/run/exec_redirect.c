/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:02:28 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/25 05:16:15 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_in(t_tree *tree)
{
	int	fd;
	int	status;

	// if (is_ambiguous(tree) == TRUE)
	// 	return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	fd = open(tree->redir_info, O_RDONLY);
	if (fd == -1)
	{
		status = is_read(tree->redir_info);
		return (status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (CODE_SUCCESS);
}

int	ft_out(t_tree *tree)
{
	int	fd;
	int	status;

	// if (is_ambiguous(tree) == TRUE)
	// 	return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	fd = open(tree->redir_info, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		status = is_write(tree->redir_info);
		return (status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (CODE_SUCCESS);
}

int	ft_append(t_tree *tree)
{
	int	fd;
	int	status;

	// if (is_ambiguous(tree) == TRUE)
	// 	return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	fd = open(tree->redir_info, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		status = is_write(tree->redir_info);
		return (status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (CODE_SUCCESS);
}

int	ft_add_redirection(t_shell_info *shell, t_tree *tree, t_tree *redirs)
{
	int	status;

	(void)shell;
	(void)tree;
	while (redirs)
	{
		status = ft_exec_redirection(shell, redirs->left);
		if (status == CODE_ERROR)
			return (status);
		if (redirs->right)
			redirs = redirs->right;
		else
			break ;
	}
	return (status);
}

int	ft_exec_redirection(t_shell_info *shell, t_tree *tree)
{
	int	status;

	(void)shell;
	status = CODE_ERROR;
	if (ft_strcmp(tree->redir, "<") == CODE_SUCCESS)
		status = ft_in(tree);
	else if (ft_strcmp(tree->redir, ">") == CODE_SUCCESS)
		status = ft_out(tree);
	else if (ft_strcmp(tree->redir, ">>") == CODE_SUCCESS)
		status = ft_append(tree);
	else if (ft_strcmp(tree->redir, "<<") == CODE_SUCCESS)
	{
		dup2(tree->here_doc, STDIN_FILENO);
		if (access(tree->tmp_file, F_OK) == 0)
			unlink(tree->tmp_file);
		close(tree->here_doc);
		status = CODE_SUCCESS;
	}
	return (status);
}
