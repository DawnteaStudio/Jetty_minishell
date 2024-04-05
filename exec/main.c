/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/05 17:09:26 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_minishell(int argc, char **argv, char **envp, t_shell_info *shell)
{
	struct termios	term;

	if (argc != 1)
	{
		ft_putstr_fd("the argc of this minishell cannot exceed 1\n", 2);
		exit(1);
	}
	(void)argv;
	shell->envp = envp;
	shell->backup_stdin = dup(0);
	shell->backup_stdout = dup(1);
	shell->env_list = NULL;
	make_env_list(shell);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	struct termios	term;
	t_shell_info	shell;

	set_minishell(argc, argv, envp, &shell);
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		set_signal(CUSTOM, IGNORE);
		str = readline("jetty_shell>");
		if (str == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (str[0] != 0)
			add_history(str);
		if (is_builtin(str))
		{
			if (!ft_strcmp(str, "env"))
				ft_env(&shell);
			else
				printf("builtin!!\n");
		}
		free(str);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}
