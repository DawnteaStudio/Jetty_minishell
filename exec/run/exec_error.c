/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:43:27 by parksewon         #+#    #+#             */
/*   Updated: 2024/04/12 22:10:47 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_exit_code	putstr_error(char *str, t_exit_code code, t_error_type type)
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
	return (code);
}
