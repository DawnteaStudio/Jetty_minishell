/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 03:15:19 by parksewon         #+#    #+#             */
/*   Updated: 2024/05/08 03:25:09 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_dollar_index(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	expand_line()
{
	int		i;
	char	*input_line;

	i = 0;
}