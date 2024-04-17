/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:56:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/17 19:31:52 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_path_line(char *path, char **envp)
{
	int		i;
	int		j;
	char	*head;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		head = ft_substr(envp[i], 0, j);
		if (ft_strcmp(head, path) == 0)
		{
			del(head);
			return (envp[i] + j + 1);
		}
		del(head);
		i++;
	}
	return (NULL);
}

char	**ft_get_all_path(t_shell_info *shell)
{
	t_env_node	*tmp;
	char		**res;

	tmp = is_include_env(&(shell->env_list), "PATH");
	if (tmp == NULL)
		res = ft_split(ft_get_path_line("PATH", shell->envp), ':');
	else
		res = ft_split(tmp->value, ':');
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
	return last_status;
}

int	ft_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

void	ft_restore_fd(t_shell_info *shell)
{
	dup2(shell->backup_stdin, 0);
	dup2(shell->backup_stdout, 1);
}
