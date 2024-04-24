/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:26:48 by parksewon         #+#    #+#             */
/*   Updated: 2024/04/25 05:15:59 by sewopark         ###   ########.fr       */
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
		free(str);
		itoa_str = ft_itoa(i);
		str = ft_strjoin(".tmp", itoa_str);
		free(itoa_str);
		i++;
	}
	return (str);
}

void	input_here_doc(t_shell_info *shell, t_tree *tree)
{
	char	*line;
	int		fd;

	set_signal(HDSIGINT, IGNORE);
	fd = open(tree->tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(tree->redir_info, line) == CODE_SUCCESS)
			break ;
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
		if (WEXITSTATUS(status) == SIGINT)
		{
			shell->heredoc_quit = TRUE;
			g_exit_code = CODE_ERROR;
		}
		else
			g_exit_code = WEXITSTATUS(status);
	}
	tree->here_doc = open(tree->tmp_file, O_RDONLY);
}
