/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/17 01:19:14 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

void	set_roop(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(CUSTOM, IGNORE);
}

int	start_exec(t_shell_info *shell)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(CHSIGINT, CUSTOM);
	ft_exec_preprocess(shell, shell->tree);
	return (ft_exec(shell, shell->tree));
}

void	set_minishell(int argc, char **argv, char **envp, t_shell_info *shell)
{
	if (argc != 1)
	{
		ft_putstr_fd("the argc of this minishell cannot exceed 1\n", 2);
		exit(1);
	}
	(void)argv;
	shell->backup_pwd = NULL;
	shell->envp = envp;
	shell->backup_stdin = dup(0);
	shell->backup_stdout = dup(1);
	shell->env_list = NULL;
	shell->pure_oldpwd = TRUE;
	make_env_list(shell);
}

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	t_shell_info	shell;

	set_minishell(argc, argv, envp, &shell);
	while (1)
	{
		set_roop();
		str = readline("jetty_shell>");
		if (str == NULL)
		{
			printf("\033[1A\033[13Cexit\n");
			break ;
		}
		if (str[0] != 0)
			add_history(str);
		shell.tree = parse(str, &(shell.env_list));
		if (shell.tree != NULL)
			g_exit_code = start_exec(&shell);
		del(str);
	}
	clean_all(&shell);
	return (CODE_SUCCESS);
}
