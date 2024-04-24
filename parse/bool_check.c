/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:20:01 by erho              #+#    #+#             */
/*   Updated: 2024/04/25 03:23:10 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_quote(char c)
{
	if (c != 34 && c != 39)
		return (FALSE);
	return (TRUE);
}

int	is_bracket(char c)
{
	if (c != '>' && c != '<')
		return (FALSE);
	return (TRUE);
}

int	is_dollar(char c)
{
	if (c != '$')
		return (FALSE);
	return (TRUE);
}

int	is_pipe(char c)
{
	if (c != '|')
		return (FALSE);
	return (TRUE);
}

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}
