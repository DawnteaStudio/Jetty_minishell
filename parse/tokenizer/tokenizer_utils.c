/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:17:11 by erho              #+#    #+#             */
/*   Updated: 2024/05/06 21:29:08 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_bracket(char *str, t_syntax *st)
{
	if (!is_bracket(str[st->width - 1]))
		return (is_bracket(str[st->width]));
	if (!is_bracket(str[st->width]))
		return (1);
	if ((str[st->width - 1] != str[st->width]) || st->len == 2)
		return (1);
	return (0);
}

int	check_sign(char *str, t_syntax *st)
{
	if (is_pipe(str[st->width]) || is_pipe(str[st->width - 1]))
		return (1);
	return (check_bracket(str, st));
}
