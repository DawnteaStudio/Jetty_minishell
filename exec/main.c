/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/04 12:34:52 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_minishell()
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	set_signal(CUSTOM, IGNORE);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	struct termios	term;

	((void)argc, (void)argv, (void)envp);
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		set_minishell();
		str = readline("jetty_shell>");
		if (str == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (str[0] != 0)
			add_history(str);
		if (is_builtin(str))
			printf("builtin!!\n");
		free(str);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}
