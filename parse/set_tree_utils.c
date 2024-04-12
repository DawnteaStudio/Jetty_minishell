/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:24:34 by erho              #+#    #+#             */
/*   Updated: 2024/04/12 02:42:49 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tree_make_word(char *s1, char *s2, t_command cmd)
{
	int	s1_idx;
	int	s2_idx;

	s1_idx = 0;
	s2_idx = 0;
	while (s1_idx < cmd.len)
	{
		if (is_quote(cmd.quotes) || is_quote(s2[s2_idx]))
		{
			if (cmd.quotes == '\0')
				cmd.quotes = s2[s2_idx++];
			while (s1_idx < cmd.len && s2[s2_idx] && (!is_quote(s2[s2_idx])
					|| s2[s2_idx] != cmd.quotes))
				s1[s1_idx++] = s2[s2_idx++];
			cmd.quotes = '\0';
		}
		else if (s2[s2_idx] == '$')
			return ;
		else
			s1[s1_idx++] = s2[s2_idx];
		s2_idx++;
	}
	s1[s1_idx] = '\0';
}

void	tree_find_idx(char *str, t_command *cmd)
{
	cmd->word = cmd->width;
	while (str[cmd->width])
	{
		if (is_quote(cmd->quotes) || is_quote(str[cmd->width]))
		{
			if (cmd->quotes == '\0')
				cmd->quotes = str[cmd->width++];
			while (str[cmd->width] && (!is_quote(str[cmd->width])
					|| str[cmd->width] != cmd->quotes))
			{
				if (cmd->quotes == '"' && str[cmd->width] == '$')
					return ;
				cmd->width++;
				cmd->len++;
			}
			cmd->quotes = '\0';
		}
		else if (str[cmd->width] == '$')
			return ;
		else
			cmd->len++;
		if (str[cmd->width] != '\0')
			cmd->width++;
	}
}

void	swap_ch(char *c1, char *c2)
{
	char	temp;

	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

char	*res_join(char **str, char **temp)
{
	char	*res;

	res = ft_strjoin(*str, *temp);
	free(*str);
	free(*temp);
	return (res);
}
