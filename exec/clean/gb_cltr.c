/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_cltr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:38:49 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/08 21:01:52 by sewopark         ###   ########.fr       */
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
}

void	clean_all(t_shell_info *shell)
{
	heap_handler(NULL);
	free_env_list(shell);
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &(shell->term));
}
