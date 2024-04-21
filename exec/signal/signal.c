/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:11:28 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/22 02:29:35 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
}

void	child_signal_handler(int num)
{
	if (num == SIGINT)
		ft_putstr_fd("\n", 1);
}

void	heredoc_signal_handler(int num)
{
	if (num == SIGINT)
		exit(CODE_ERROR);
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == CUSTOM)
		signal(SIGINT, signal_handler);
	if (sig_quit == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == CUSTOM)
		signal(SIGQUIT, signal_handler);
	if (sig_int == CHSIGINT)
		signal(SIGINT, child_signal_handler);
	if (sig_int == HDSIGINT)
		signal(SIGINT, heredoc_signal_handler);
}
