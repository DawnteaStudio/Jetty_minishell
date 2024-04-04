/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:17:11 by erho              #+#    #+#             */
/*   Updated: 2024/04/04 15:35:21 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_quote(char c)
{
	if (c != 34 && c != 39)
		return (0);
	return (1);
}

int check_redirection(char *str, t_command *cmd)
{
	if (cmd->width >= 1 
			&& str[cmd->width - 1] != '<' && str[cmd->width - 1] != '>')
	{
		if (str[cmd->width] == '<' || str[cmd->width] == '>')
			return (1);
	}
	if ((str[cmd->width] != '<' && str[cmd->width] != '>') || cmd->len == 2)
		return (1);
	return (0);
}
