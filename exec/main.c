/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/03/24 20:49:06 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	struct termios	term;

	(void)term;
	((void)argc, (void)argv, (void)envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		str = readline("jetty_shell>");
		if (str == NULL)
			break ;
		add_history(str);
		free(str);
	}
	return (0);
}
