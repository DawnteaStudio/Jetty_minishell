/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:43:27 by parksewon         #+#    #+#             */
/*   Updated: 2024/04/25 00:04:10 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*find_token_key(t_tree *tree)
// {
// 	int	i;

// 	i = 0;
// 	while(tree->origin_token[i])
// 	{
		
// 	}
// }

// int	is_ambiguous(t_tree *tree)
// {
// 	int	i;
// 	int	is_true;

// 	i = 0;
// 	is_true = FALSE;
// 	while (tree->origin_token && tree->origin_token[i])
// 	{
// 		if (tree->origin_token[i] == '$')
// 		{
// 			is_true = TRUE;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (is_true == FALSE)
// 		return (FALSE);
	
// }

t_exit_code	putstr_error(char *str, t_exit_code code, t_error_type type)
{
	if (type == ERR_PERROR)
		perror("");
	else
	{
		ft_putstr_fd("jetty: ", 2);
		ft_putstr_fd(str, 2);
		if (type == ERR_CMD_NOT_FND)
			ft_putstr_fd(": command not found\n", 2);
		else if (type == ERR_NO_SUCH_FILE)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (type == ERR_PER_DENIED)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (type == ERR_AMBIGUOUS)
			ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	return (code);
}
