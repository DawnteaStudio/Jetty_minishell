/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 06:49:29 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/06 21:47:17 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_is_over(unsigned long int res, int sign, const char c)
{
	if (res > LM)
		return (FALSE);
	else if (res == LM)
	{
		if (sign == -1 && (c - '0') > 8)
			return (FALSE);
		else if (sign == 1 && (c - '0') > 7)
			return (FALSE);
	}
	return (TRUE);
}

int	is_wide_num(char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (ft_is_over(result, sign, str[i]) == FALSE)
			return (ft_is_over(result, sign, str[i]));
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (TRUE);
}

int	is_num(char	*str)
{
	int	i;
	int	meet_blank;

	i = 0;
	meet_blank = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 0)
		return (FALSE);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i] == ' ' || str[i] == '\t')
				meet_blank = 1;
			else
				return (FALSE);
		}
		else if (meet_blank == 1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_exit(t_shell_info *shell, t_tree *tree)
{
	if (tree->exp[1])
	{
		if (tree->exp[2])
		{
			ft_putstr_fd("exit\njetty_shell: exit: too many arguments\n", 2);
			return (CODE_ERROR);
		}
		else if (is_num(tree->exp[1]) == FALSE || \
		is_wide_num(tree->exp[1]) == FALSE)
		{
			ft_putstr_fd("exit\njetty_shell: exit: ", 2);
			ft_putstr_fd(tree->exp[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			clean_all(shell);
			exit(CODE_255);
		}
		else
			g_exit_code = (ft_atoi(tree->exp[1]) % 256);
	}
	clean_all(shell);
	ft_putstr_fd("exit\n", 1);
	exit(g_exit_code);
	return (g_exit_code);
}
