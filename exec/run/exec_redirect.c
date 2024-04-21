/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:02:28 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/22 04:04:45 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_in(t_tree *tree)
{
	int	fd;
	int	status;

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

void	ft_add_redirection(t_shell_info *shell, t_tree *tree, t_tree *redirs)
{
	(void)shell;
	(void)tree;
	while (redirs)
	{
		ft_exec_redirection(redirs->left);
		if (redirs->right)
			redirs = redirs->right;
		else
			break ;
	}
}

int	ft_exec_redirection(t_tree *tree)
{
	int	status;

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
		close(tree->here_doc);
		status = CODE_SUCCESS;
	}
	return (status);
}
