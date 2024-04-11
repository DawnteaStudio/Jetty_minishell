/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:50:58 by erho              #+#    #+#             */
/*   Updated: 2024/03/24 21:18:13 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main()
{
	char	*str;
	t_token *tokens;

	while (1)
	{
		str = readline("jetty_shell>");
		if (str == NULL)
			break ;
		add_history(str);
		tokens = lexical_analyze(str);
		int idx = 0;
		while (tokens[idx].str)
		{
			printf("%s\n", tokens[idx].str);
			idx++;
		}
		free(str);
	}
	return (0);
}