/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:50:58 by erho              #+#    #+#             */
/*   Updated: 2024/04/21 19:12:36 by erho             ###   ########.fr       */
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
			printf("%s ", tree->exp[i]);
			i++;
		}
		printf("\n");
	}
	if (tree->left != NULL)
		print_tree_type(tree->left);
	if (tree->right != NULL)
		print_tree_type(tree->right);
}

int	main(int argc, char **argv, char **envp)
{
	t_tree			*tree;
	char			*str;
	t_env_node *env_list = create_list("PATH", "test success");

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		str = readline("jetty_shell>");
		if (str == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (str[0] == 0)
		{
			free(str);
			continue ;
		}
		add_history(str);
		tree = parse(str, &env_list);
		if (tree != NULL)
		{
			print_tree_type(tree);
			free_tree(&tree);
		}
		free(str);
	}
	return (g_exit_code);
}
