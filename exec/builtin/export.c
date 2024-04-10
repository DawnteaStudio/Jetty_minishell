/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:21:18 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/10 09:36:58 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_print_export_error(char *str)
{
	ft_putstr_fd("jetty: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (CODE_ERROR);
}

void	ft_print_export_list(t_shell_info *shell)
{
	t_env_node	*list;
	int			i;

	list = shell->env_list;
	while (list)
	{
		i = 0;
		if (list->value && (ft_strcmp(list->key, "_") != 0))
		{
			printf("declare -x %s=\"", list->key);
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					printf("\\%c", (list->value)[i++]);
				else
					printf("%c", (list->value)[i++]);
			}
			printf("\"\n");
		}
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

int	ft_export(t_shell_info *shell)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = CODE_SUCCESS;
	if (shell->d_array[1] == NULL)
		ft_print_export_list(shell);
	else
	{
		while (shell->d_array[i])
		{
			if (is_valid_key(shell->d_array[i]) == FALSE)
				exit_code = ft_print_export_error(shell->d_array[i]);
			else
				make_env_component(&(shell->env_list), shell->d_array[i]);
			i++;
		}
	}
	return (exit_code);
}
