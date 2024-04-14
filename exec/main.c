/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/12 09:44:15 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

void	set_minishell(int argc, char **argv, char **envp, t_shell_info *shell)
{
	struct termios	term;

	if (argc != 1)
	{
		ft_putstr_fd("the argc of this minishell cannot exceed 1\n", 2);
		exit(1);
	}
	(void)argv;
	shell->backup_pwd = ft_strdup("");
	shell->oldpwd = 1;
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
	t_shell_info	shell;
	t_tree			tree;

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
		tree.exp = ft_split(str, ' ');
		tree.cmd = tree.exp[0];
		ft_exec(&shell, tree.cmd);
		free(str);
	}
	clean_all(&shell);
	return (g_exit_code);
}
