/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:20:01 by erho              #+#    #+#             */
/*   Updated: 2024/04/08 20:20:02 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_quote(char c)
{
	if (c != 34 && c != 39)
		return (0);
	return (1);
}

int	is_bracket(char c)
{
	if (c != '>' && c != '<')
		return (0);
	return (1);
}

int	is_dollar(char c)
{
	if (c != '$')
		return (0);
	return (1);
}

int	is_pipe(char c)
{
	if (c != '|')
		return (0);
	return (1);
}