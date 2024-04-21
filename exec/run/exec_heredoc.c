/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:26:48 by parksewon         #+#    #+#             */
/*   Updated: 2024/04/22 03:20:12 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	input_here_doc(t_shell_info *shell, t_tree *tree, int fd)
{
	char	*line;

	set_signal(HDSIGINT, IGNORE);
	fd = open(shell->heredoc_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(tree->redir_info, line) == CODE_SUCCESS)
			break;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	clean_all(shell);
	exit(CODE_SUCCESS);
}



void	ft_here_doc(t_shell_info *shell, t_tree *tree)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	set_signal(CUSTOM, IGNORE);
	if (!pid)
		input_here_doc(shell, tree, fd[1]);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		set_signal(CHSIGINT, CUSTOM);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			shell->heredoc_quit = TRUE;
			g_exit_code = CODE_ERROR;
		}
	}
	tree->here_doc = fd[0];
}
