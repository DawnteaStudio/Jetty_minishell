/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/01 20:48:26 by sewopark         ###   ########.fr       */
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

	set_signal(CHSIGINT, CUSTOM);
	ft_exec_preprocess(shell, shell->tree);
	if (shell->heredoc_quit == TRUE)
	{
		shell->heredoc_quit = FALSE;
		return (g_exit_code);
	}
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
	shell->tree = NULL;
	shell->backup_pwd = NULL;
	shell->backup_oldpwd = NULL;
	shell->envp = envp;
	shell->backup_stdin = dup(0);
	shell->backup_stdout = dup(1);
	shell->env_list = NULL;
	shell->pure_oldpwd = TRUE;
	shell->cd_before = FALSE;
	shell->heredoc_quit = FALSE;
	shell->origin = TRUE;
	shell->path_avil = TRUE;
	shell->env = NULL;
	make_env_list(shell);
	shell->backup_pocket = make_backup_env();
}

void	start_parse(t_shell_info *shell, char *str)
{
	shell->tree = parse(str, &(shell->env_list));
	if (shell->tree != NULL)
	{
		g_exit_code = start_exec(shell);
		free_tree(&(shell->tree));
	}
}

void leaks()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	t_shell_info	shell;

	atexit(leaks);
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
		if (str[0] == 0)
		{
			del(str);
			continue ;
		}
		add_history(str);
		start_parse(&shell, str);
		del(str);
	}
	clean_all(&shell);
	return (CODE_SUCCESS);
}
