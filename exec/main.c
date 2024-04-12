/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/12 23:43:51 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

int	start_exec(t_shell_info *shell, t_tree *tree)
{
	set_signal(DEFAULT, CUSTOM);
	tcsetattr(STDIN_FILENO, TCSANOW, &(shell->term));
	return (ft_exec(shell, tree));
}

void	set_minishell(int argc, char **argv, char **envp, t_shell_info *shell)
{
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
}

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	t_shell_info	shell;
	t_tree			*tree;

	shell.tree = &tree;
	tcgetattr(STDIN_FILENO, &(shell.term));
	set_minishell(argc, argv, envp, &shell);
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
		tree = parse(str, &(shell.env_list));
		g_exit_code = start_exec(&shell, tree);
		free(str);
	}
	clean_all(&shell);
	return (g_exit_code);
}
