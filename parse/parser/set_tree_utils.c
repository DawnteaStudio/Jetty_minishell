/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:24:34 by erho              #+#    #+#             */
/*   Updated: 2024/05/05 14:36:01 by erho             ###   ########.fr       */
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

char	*res_join(char *str, char *temp)
{
	char	*res;

	res = ft_strjoin(str, temp);
	free(str);
	return (res);
}

char	**set_exp()
{
	char	**res;

	res = (char **)malloc(sizeof(char *));
	if (res == NULL)
		exit(1);
	res[0] = NULL;
	return (res);
}

char	**join_exp_n_str(char **exp, char **str)
{
	int		cnt;
	char	**new_exp;
	int		i;

	cnt = cnt_exp(exp) + 1;
	new_exp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (new_exp == NULL)
		exit(1);
	new_exp[cnt] = NULL;
	i = 0;
	while (exp[i])
	{
		new_exp[i] = exp[i];
		i++;
	}
	new_exp[i] = ft_strdup(*str);
	free(exp[cnt - 1]);
	free(exp);
	free(*str);
	return (new_exp);
}
