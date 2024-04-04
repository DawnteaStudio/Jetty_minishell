/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:06:56 by erho              #+#    #+#             */
/*   Updated: 2024/04/04 15:32:11 by erho             ###   ########.fr       */
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
			while (s[cmd->width] && (s[cmd->width] != cmd->quotes
					|| !is_quote(s[cmd->width])))
			{
				cmd->width++;
				cmd->len++;
			}
		}
		cmd->len++;
		if (s[cmd->width])
			cmd->width++;
		if (check_redirection(s, cmd))
			break ;
	}
}

char	**ft_insert(char *s, char **res, char c, t_command cmd)
{
	while (s[cmd.width])
	{
		cmd.len = 0;
		find_idx(&cmd, s, c);
		if (cmd.width > cmd.word)
		{
			res[cmd.height] = (char *)malloc(sizeof(char) * (cmd.len + 1));
			if (res[cmd.height] == NULL)
				exit(1);
			make_word(res[cmd.height], &s[cmd.word], &cmd);
			res[cmd.height][cmd.len] = '\0';
			cmd.height++;
		}
	}
	return (res);
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

char	**tokenize(char *s, char c)
{
	int			cnt;
	char		**res;
	t_command	cmd;

	cmd.width = 0;
	cmd.height = 0;
	cmd.word_count = 0;
	cmd.len = 0;
	cnt = count_word(s, c, cmd);
	res = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (res == NULL)
		exit(1);
	res = ft_insert(s, res, c, cmd);
	if (res != NULL)
		res[cnt] = NULL;
	return (res);
}
