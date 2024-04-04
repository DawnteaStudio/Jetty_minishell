/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:15:16 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/04 17:54:29 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_env_node(char	*env_line)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
		{
			key = ft_keymake(); // will be make
			break ;
		}
		i++;
	}
	i++;
	while (env_line[i])
	{
		
	}	
}

t_env_node	*make_env_list(char **envp)
{
	t_env_node	new_env_list;
	int			i;

	ft_memset(&new_env_list, 0, sizeof(t_env_node));
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		
	}
}
