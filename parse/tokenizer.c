/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:06:56 by erho              #+#    #+#             */
/*   Updated: 2024/04/08 20:20:14 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_word(char *s1, char *s2, t_command *cmd)
{
	int	idx;

	idx = 0;
	while (idx < cmd->len)
	{
		s1[idx] = s2[idx];
		idx++;
	}
}

void	find_idx(t_command *cmd, char *s, char c)
{
	while (s[cmd->width] && s[cmd->width] == c)
		cmd->width++;
	if (s[cmd->width])
		cmd->word_count++;
	cmd->word = cmd->width;
	while (s[cmd->width] && s[cmd->width] != c)
	{
		if (is_quote(s[cmd->width]))
		{
			cmd->quotes = s[cmd->width];
			cmd->width++;
			cmd->len++;
			while (s[cmd->width] && (!is_quote(s[cmd->width])
					|| s[cmd->width] != cmd->quotes))
			{
				cmd->width++;
				cmd->len++;
			}
		}
		cmd->len++;
		if (s[cmd->width])
			cmd->width++;
		if (check_sign(s, cmd))
			break ;
	}
}

void	ft_insert(char *s, t_token *res, char c, t_command cmd)
{
	while (s[cmd.width])
	{
		cmd.len = 0;
		find_idx(&cmd, s, c);
		if (cmd.width > cmd.word)
		{
			res[cmd.height].str = (char *)malloc(sizeof(char) * (cmd.len + 1));
			if (res[cmd.height].str == NULL)
				exit(1);
			make_word(res[cmd.height].str, &s[cmd.word], &cmd);
			(res[cmd.height].str)[cmd.len] = '\0';
			cmd.height++;
		}
	}
}

int	count_word(char *s, char c, t_command cmd)
{
	while (s[cmd.width])
	{
		cmd.len = 0;
		find_idx(&cmd, s, c);
	}
	return (cmd.word_count);
}

t_token *tokenize(char *s, char c)
{
	int			cnt;
	t_token		*res;
	t_command	cmd;

	ft_memset(&cmd, 0, sizeof(t_command));
	cnt = count_word(s, c, cmd);
	res = (t_token *)malloc(sizeof(t_token) * (cnt + 1));
	if (res == NULL)
		exit(1);
	ft_insert(s, res, c, cmd);
	res[cnt].str = NULL;
	return (res);
}
