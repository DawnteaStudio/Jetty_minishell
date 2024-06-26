/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:26:48 by parksewon         #+#    #+#             */
/*   Updated: 2024/05/08 20:36:16 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*make_tmp_file_name(void)
{
	char	*str;
	char	*itoa_str;
	int		i;

	i = 0;
	str = ft_strjoin(".tmp", "");
	while (access(str, F_OK) == 0)
	{
		del(&str);
		itoa_str = ft_itoa(i);
		str = ft_strjoin(".tmp", itoa_str);
		del(&itoa_str);
		i++;
	}
	return (str);
}

void	write_here_doc(t_shell_info *shell, t_tree *tree, int fd)
{
	size_t	start;
	size_t	end;

	while (1)
	{
		shell->here_doc = readline("> ");
		start = 0;
		end = 0;
		if (!shell->here_doc || \
		ft_strcmp(tree->redir_info[0], shell->here_doc) == CODE_SUCCESS)
			break ;
		if (is_no_quotes(tree->origin_token) == TRUE)
			write_loop(shell, fd, &start, &end);
		else
			ft_putstr_fd(shell->here_doc, fd);
		ft_putstr_fd("\n", fd);
		del(&shell->here_doc);
	}
	if (shell->here_doc)
		del(&shell->here_doc);
}

void	input_here_doc(t_shell_info *shell, t_tree *tree)
{
	int		fd;

	set_signal(HDSIGINT, IGNORE);
	fd = open(tree->tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write_here_doc(shell, tree, fd);
	close(fd);
	fd = open(tree->tmp_file, O_RDONLY, 0644);
	clean_all(shell);
	if (fd == -1)
		exit(ERR_NOFILE);
	close(fd);
	exit(CODE_SUCCESS);
}

void	ft_parent_here_doc(t_shell_info *shell, t_tree *tree, int *status)
{
	int	return_status;

	return_status = WEXITSTATUS(*status);
	if (return_status == SIGINT || return_status == ERR_NOFILE)
	{
		shell->heredoc_quit = TRUE;
		g_exit_code = CODE_ERROR;
		if (return_status == ERR_NOFILE)
		{
			ft_putstr_fd("jetty: ", 2);
			ft_putstr_fd(tree->tmp_file, 2);
			ft_putstr_fd(": is not exist\n", 2);
		}
	}
	else
	{
		g_exit_code = return_status;
		tree->here_doc = open(tree->tmp_file, O_RDONLY);
	}
}

void	ft_here_doc(t_shell_info *shell, t_tree *tree)
{
	int		status;
	pid_t	pid;

	if (shell->heredoc_quit == TRUE)
		return ;
	signal(SIGQUIT, SIG_IGN);
	tree->tmp_file = heap_handler(make_tmp_file_name());
	pid = fork();
	if (!pid)
		input_here_doc(shell, tree);
	else
	{
		waitpid(pid, &status, 0);
		set_signal(CHSIGINT, CUSTOM);
		ft_parent_here_doc(shell, tree, &status);
	}
}
