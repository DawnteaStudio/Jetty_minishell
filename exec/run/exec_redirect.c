/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:02:28 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/07 01:47:46 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_in(t_tree *tree)
{
	int	fd;
	int	status;

	if (tree->redir_info[1] != NULL)
		return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	if (tree->redir_info[0][0] == 0 && null_amb(tree->origin_token))
		return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	fd = open(tree->redir_info[0], O_RDONLY);
	if (fd == -1)
	{
		status = is_read(tree->redir_info[0]);
		return (status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (CODE_SUCCESS);
}

int	ft_out(t_tree *tree)
{
	int			fd;
	int			status;
	struct stat	statbuf;

	if (tree->redir_info[1] != NULL)
		return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	if (tree->redir_info[0][0] == 0 && null_amb(tree->origin_token))
		return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	if (stat(tree->redir_info[0], &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			return (putstr_error(tree->redir_info[0], CODE_ERROR, ERR_ISDIR));
	}
	fd = open(tree->redir_info[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		status = is_write(tree->redir_info[0]);
		return (status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (CODE_SUCCESS);
}

int	ft_append(t_tree *tree)
{
	int			fd;
	int			status;
	struct stat	statbuf;

	if (tree->redir_info[1] != NULL)
		return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	if (tree->redir_info[0][0] == 0 && null_amb(tree->origin_token))
		return (putstr_error(tree->origin_token, CODE_ERROR, ERR_AMBIGUOUS));
	if (stat(tree->redir_info[0], &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			return (putstr_error(tree->redir_info[0], CODE_ERROR, ERR_ISDIR));
	}
	fd = open(tree->redir_info[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		status = is_write(tree->redir_info[0]);
		return (status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (CODE_SUCCESS);
}

int	ft_add_redirection(t_tree *redirs)
{
	int	status;

	status = CODE_SUCCESS;
	while (redirs)
	{
		status = ft_exec_redirection(redirs->left);
		if (status == CODE_ERROR)
			return (status);
		if (redirs->right)
			redirs = redirs->right;
		else
			break ;
	}
	return (status);
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
		if (access(tree->tmp_file, F_OK) == 0)
			unlink(tree->tmp_file);
		close(tree->here_doc);
		status = CODE_SUCCESS;
	}
	return (status);
}
