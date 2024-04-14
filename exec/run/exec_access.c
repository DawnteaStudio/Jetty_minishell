/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:39:57 by parksewon         #+#    #+#             */
/*   Updated: 2024/04/12 23:06:30 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_exit_code	is_read(char *file)
{
	if (file[0] == 0)
		return(putstr_error(file, CODE_ERROR, ERR_NO_SUCH_FILE));
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return (file, CODE_ERROR, ERR_PER_DENIED);
		return (CODE_SUCCESS);
	}
	return (file, CODE_ERROR, ERR_NO_SUCH_FILE);
}

t_exit_code	is_write(char *file)
{
	if (file[0] == 0)
		return(putstr_error(file, CODE_ERROR, ERR_NO_SUCH_FILE));
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return (file, CODE_ERROR, ERR_PER_DENIED);
		return (CODE_SUCCESS);
	}
	return (file, CODE_ERROR, ERR_NO_SUCH_FILE);
}

t_exit_code	is_append(char *file)
{
	if (file[0] == 0)
		return(putstr_error(file, CODE_ERROR, ERR_NO_SUCH_FILE));
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return (file, CODE_ERROR, ERR_PER_DENIED);
		return (CODE_SUCCESS);
	}
	return (file, CODE_ERROR, ERR_NO_SUCH_FILE);
}
