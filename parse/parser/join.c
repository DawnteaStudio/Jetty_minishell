/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:59:42 by erho              #+#    #+#             */
/*   Updated: 2024/05/06 18:29:54 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*str_join(char *str, char *temp)
{
	char	*res;

	res = ft_strjoin(str, temp);
	free(str);
	return (res);
}

char	**join_exp(char **tree_exp, char **tmp, int exp_len)
{
	int		cnt;
	char	**new_exp;

	cnt = exp_len + cnt_exp(tmp);
	new_exp = set_exp(cnt);
	cpy_new_exp(new_exp, tree_exp, tmp, exp_len);
	free(tree_exp);
	free(tmp);
	return (new_exp);
}

char	**join_exp_n_str(char **exp, char *str, t_syntax *st)
{
	char	**new_exp;
	int		i;

	if (exp[st->height] || str[0] == '\0')
	{
		if (str[0] != '\0')
			exp[st->height] = str_join(exp[st->height], str);
		free(str);
		return (exp);
	}
	new_exp = set_exp(cnt_exp(exp));
	i = 0;
	while (i < st->height)
	{
		new_exp[i] = exp[i];
		i++;
	}
	st->height = i;
	if (exp[i])
		new_exp[i] = str_join(exp[i], str);
	else
		new_exp[i] = ft_strdup(str);
	free(exp);
	free(str);
	return (new_exp);
}
