/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:06:56 by erho              #+#    #+#             */
/*   Updated: 2024/05/01 22:30:57 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_word(char *s1, char *s2, t_syntax *st)
{
	int	idx;

	idx = 0;
	while (idx < st->len)
	{
		s1[idx] = s2[idx];
		idx++;
	}
}

void	find_idx(t_syntax *st, char *s)
{
	while (s[st->width] && is_white_space(s[st->width]))
		st->width++;
	if (s[st->width])
		st->word_count++;
	st->word = st->width;
	while (s[st->width] && !is_white_space(s[st->width]))
	{
		if (is_quote(s[st->width]))
		{
			st->quotes = s[st->width];
			st->width++;
			st->len++;
			while (s[st->width] && (!is_quote(s[st->width])
					|| s[st->width] != st->quotes))
			{
				st->width++;
				st->len++;
			}
		}
		st->len++;
		if (s[st->width])
			st->width++;
		if (check_sign(s, st))
			break ;
	}
}

void	ft_insert(char *s, t_token *res, t_syntax st)
{
	if (s[st.width] == '\0')
		res[st.height].str = ft_strdup("");
	while (s[st.width])
	{
		st.len = 0;
		find_idx(&st, s);
		if (st.width > st.word)
		{
			res[st.height].str = (char *)malloc(sizeof(char) * (st.len + 1));
			if (res[st.height].str == NULL)
				exit(1);
			make_word(res[st.height].str, &s[st.word], &st);
			(res[st.height].str)[st.len] = '\0';
			st.height++;
		}
	}
}

int	count_word(char *s, t_syntax cmd)
{
	if (s[cmd.width] == '\0')
		cmd.word_count++;
	while (s[cmd.width])
	{
		cmd.len = 0;
		find_idx(&cmd, s);
	}
	return (cmd.word_count);
}

t_token	*tokenize(char *s)
{
	int			cnt;
	t_token		*res;
	t_syntax	cmd;

	ft_memset(&cmd, 0, sizeof(t_syntax));
	cnt = count_word(s, cmd);
	res = (t_token *)malloc(sizeof(t_token) * (cnt + 1));
	if (res == NULL)
		exit(1);
	ft_insert(s, res, cmd);
	res[cnt].str = NULL;
	return (res);
}
