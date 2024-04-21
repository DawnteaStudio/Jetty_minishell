/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_cltr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:38:49 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/22 03:13:55 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	del(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

char	*heap_handler(char *ptr)
{
	static t_list	*list;

	if (ptr == NULL)
		ft_lstclear(&list, del);
	else
		ft_lstadd_back(&list, ft_lstnew(ptr));
	return (ptr);
}

void	free_env_list(t_shell_info *shell)
{
	t_env_node	*env_list;
	t_env_node	*free_node;

	env_list = shell->env_list;
	while (env_list)
	{
		free_node = env_list;
		env_list = env_list->next;
		free(free_node);
	}
	shell->env_list = NULL;
	if (shell->backup_pwd)
		free(shell->backup_pwd);
}

void	clean_all(t_shell_info *shell)
{
	struct termios	term;

	if (shell->tree)
		free_tree(&(shell->tree));
	if (access(shell->heredoc_tmp, F_OK) == 0)
		unlink(shell->heredoc_tmp);
	heap_handler(NULL);
	free_env_list(shell);
	rl_clear_history();
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
