/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:43:27 by parksewon         #+#    #+#             */
/*   Updated: 2024/05/06 22:53:03 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rearrange_exp(t_tree *tree, int i)
{
	while (tree->exp[i + 1])
	{
		free(tree->exp[i]);
		tree->exp[i] = ft_strdup(tree->exp[i + 1]);
		i++;
	}
	free(tree->exp[i]);
	tree->exp[i] = NULL;
}

int	is_only_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ignore_white_node(t_shell_info *shell, t_tree *tree)
{
	int		i;
	t_token	*token;

	i = 0;
	token = tokenize(shell->str);
	while (tree->exp && tree->exp[i])
	{
		if (tree->exp[i][0] == 0 && is_only_dollar(token[i].str) == TRUE)
			rearrange_exp(tree, i);
		else
			i++;
	}
	free_tokens(token);
}

int	null_amb(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_exit_code	putstr_error(char *str, t_exit_code code, t_error_type type)
{
	if (type == ERR_PERROR)
		perror("");
	else
	{
		ft_putstr_fd("jetty: ", 2);
		ft_putstr_fd(str, 2);
		if (type == ERR_CMD_NOT_FND)
			ft_putstr_fd(": command not found\n", 2);
		else if (type == ERR_NO_SUCH_FILE)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (type == ERR_PER_DENIED)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (type == ERR_AMBIGUOUS)
			ft_putstr_fd(": ambiguous redirect\n", 2);
		else if (type == ERR_ISDIR)
			ft_putstr_fd(": is a directory\n", 2);
	}
	return (code);
}
