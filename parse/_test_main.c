/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:50:58 by erho              #+#    #+#             */
/*   Updated: 2024/04/17 19:24:26 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

void	print_tree_type(t_tree *tree)
{
	if (tree->type == TREE_TYPE_REDIRECTION)
		printf("%s %s\n", tree->redir, tree->redir_info);
	else if (tree->type == TREE_TYPE_COMMAND)
	{
		printf("%s\n", tree->cmd);
		int i=0;
		while (tree->exp && tree->exp[i])
		{
			printf("cmd opt: %s\n", tree->exp[i]);
			i++;
		}
	}
	if (tree->left != NULL)
		print_tree_type(tree->left);
	if (tree->right != NULL)
		print_tree_type(tree->right);
}

// void	set_minishell(int argc, char **argv, char **envp, t_shell_info *shell)
// {
// 	struct termios	term;

// 	if (argc != 1)
// 	{
// 		ft_putstr_fd("the argc of this minishell cannot exceed 1\n", 2);
// 		exit(1);
// 	}
// 	(void)argv;
// 	shell->envp = envp;
// 	shell->backup_stdin = dup(0);
// 	shell->backup_stdout = dup(1);
// 	shell->env_list = NULL;
// 	make_env_list(shell);
// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~(ECHOCTL);
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }
int	main(int argc, char **argv, char **envp)
{
	t_tree			*tree;
	char			*str;
	// t_token 		*tokens;
	// t_shell_info	shell;
	t_env_node *env_list = create_list("PATH", "test success");

	(void)argc;
	(void)argv;
	(void)envp;
	// tcgetattr(STDIN_FILENO, &(shell.term));
	// set_minishell(argc, argv, envp, &shell);
	while (1)
	{
		// set_signal(CUSTOM, IGNORE);
		str = readline("jetty_shell>");
		if (str == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (str[0] != 0)
			add_history(str);
		tree = parse(str, &env_list);
		if (tree != NULL)
		{
			print_tree_type(tree);
			free_tree(&tree);
		}
		// tokens = lexical_analyze(str);
		// int idx = 0;
		// while (tokens[idx].str)
		// {
		// 	printf("%s\n", extract_data(tokens[idx].str, &env_list));
		// 	idx++;
		// }
		free(str);
	}
	// clean_all(&shell);
	return (g_exit_code);
}
