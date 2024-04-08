/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:17:11 by erho              #+#    #+#             */
/*   Updated: 2024/04/08 21:57:34 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_bracket(char *str, t_command *cmd)
{
	if (!is_bracket(str[cmd->width - 1]))
		return (is_bracket(str[cmd->width]));
	if (!is_bracket(str[cmd->width]))
		return (1);
	if ((str[cmd->width - 1] != str[cmd->width]) || cmd->len == 2)
		return (1);
	return (0);
}

int check_sign(char *str, t_command *cmd)
{
	if (is_dollar(str[cmd->width]) && !is_dollar(str[cmd->width - 1]))
		return (1);
	if (is_pipe(str[cmd->width]) || is_pipe(str[cmd->width - 1]))
		return (1);
	return (check_bracket(str, cmd));
}
