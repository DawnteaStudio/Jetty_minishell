/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:43:27 by parksewon         #+#    #+#             */
/*   Updated: 2024/05/06 20:21:56 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	is_all_white_space(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str && str[i])
// 	{
// 		if (is_white_space(str[i]) == FALSE)
// 			return (CODE_ERROR);
// 		i++;
// 	}
// 	return (CODE_SUCCESS);
// }

int	is_only_dollar_sign(char *str)
{
	int	i;
	int	flag;

	i  = 0;
	flag = CODE_SUCCESS;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = CODE_ERROR;
			return (CODE_ERROR);
		}
		i++;
	}
	return (CODE_SUCCESS);
}

void	ignore_white_node(t_shell_info *shell, t_tree *tree)
{
	int		i;
	t_token	*token;

	i = 0;
	token = tokenize(shell->str);
	while (tree->exp && tree->exp[i])
	{
		if (tree->exp[i][0] == 0 && is_only_dollar_sign(token[i].str) == CODE_SUCCESS)
		{
			free(tree->exp[i]);
			tree->exp[i] = NULL;
		}
		// else if (is_all_white_space(tree->exp[i]) == CODE_SUCCESS)
		// {
		// 	if (is_only_dollar_sign(token[i].str) == CODE_SUCCESS)
		// 	{
		// 		free(tree->exp[i]);
		// 		tree->exp[i] = NULL;
		// 	}
		// }
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
	}
	return (code);
}
