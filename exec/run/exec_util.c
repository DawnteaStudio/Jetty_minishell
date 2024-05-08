/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:56:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/09 00:28:49 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_len(t_env_node *list)
{
	int	len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}

char	**ft_get_all_path(t_shell_info *shell)
{
	t_env_node	*tmp;
	char		**res;

	tmp = is_include_env(&(shell->env_list), "PATH");
	if (tmp)
		res = ft_split(tmp->value, ':');
	else if (shell->path_avil == TRUE)
		res = ft_split(ENV_PATH, ':');
	else
		res = NULL;
	return (res);
}

int	ft_close_and_wait(int *status, int fd[2], pid_t	pid_right)
{
	int	last_status;

	close(fd[0]);
	close(fd[1]);
	if (waitpid(-1, &(*status), 0) == pid_right)
		last_status = *status;
	if (waitpid(-1, &(*status), 0) == pid_right)
		last_status = *status;
	return (last_status);
}

int	ft_exit_status(int status, int piped)
{
	if (WIFSIGNALED(status))
	{
		if (128 + WTERMSIG(status) == 130 && piped == FALSE)
			ft_putstr_fd("\n", 1);
		else if (128 + WTERMSIG(status) == 131 && piped == FALSE)
			ft_putstr_fd("Quit: 3\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}

int	ft_restore_fd(t_shell_info *shell, int status)
{
	dup2(shell->backup_stdin, 0);
	dup2(shell->backup_stdout, 1);
	return (status);
}
