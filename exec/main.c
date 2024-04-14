/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/14 16:58:26 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

int	start_exec(t_shell_info *shell)
{
	set_signal(DEFAULT, CUSTOM);
	tcsetattr(STDIN_FILENO, TCSANOW, &(shell->term));
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
	shell->backup_pwd = ft_strdup("");
	shell->unset_pwd = 1;
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

	tcgetattr(STDIN_FILENO, &(shell.term));
	set_minishell(argc, argv, envp, &shell);
	while (1)
	{
		set_signal(CUSTOM, IGNORE);
		str = readline("jetty_shell>");
		if (str == NULL)
		{
			printf("\033[1A\033[13Cexit\n");
			break ;
		}
		if (str[0] != 0)
			add_history(str);
		shell.tree = parse(str, &(shell.env_list));
		g_exit_code = start_exec(&shell);
		free(str);
	}
	clean_all(&shell);
	return (CODE_SUCCESS);
}
