/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:24:34 by erho              #+#    #+#             */
/*   Updated: 2024/05/06 20:23:25 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tree_make_word(char *s1, char *s2, t_syntax st)
{
	int	s1_idx;
	int	s2_idx;

	s1_idx = 0;
	s2_idx = 0;
	while (s1_idx < st.len)
	{
		if (is_quote(st.q_back_up) || is_quote(s2[s2_idx]))
		{
			if (st.q_back_up == '\0')
				st.q_back_up = s2[s2_idx++];
			while (s1_idx < st.len && s2[s2_idx] && (!is_quote(s2[s2_idx])
					|| s2[s2_idx] != st.q_back_up))
				s1[s1_idx++] = s2[s2_idx++];
			st.q_back_up = '\0';
		}
		else if (s2[s2_idx] == '$')
			return ;
		else
			s1[s1_idx++] = s2[s2_idx];
		s2_idx++;
	}
	s1[s1_idx] = '\0';
}

void	tree_find_idx(char *str, t_syntax *st)
{
	st->word = st->width;
	while (str[st->width])
	{
		if (is_quote(st->quotes) || is_quote(str[st->width]))
		{
			if (st->quotes == '\0')
				st->quotes = str[st->width++];
			while (str[st->width] && (!is_quote(str[st->width])
					|| str[st->width] != st->quotes))
			{
				if (st->quotes == '"' && str[st->width] == '$')
					return ;
				st->width++;
				st->len++;
			}
			st->quotes = '\0';
		}
		else if (str[st->width] == '$')
			return ;
		else
			st->len++;
		if (str[st->width] != '\0')
			st->width++;
	}
}

char	**set_exp(int size)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		ft_error(MEMORY);
	res[size] = NULL;
	return (res);
}

char	**make_exp(t_token *new_token)
{
	int		cnt;
	char	**res;
	int		i;

	cnt = cnt_token(new_token);
	res = set_exp(cnt);
	i = 0;
	while (new_token[i].str)
	{
		res[i] = ft_strdup(new_token[i].str);
		i++;
	}
	free_tokens(new_token);
	return (res);
}
