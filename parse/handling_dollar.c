/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 02:21:04 by erho              #+#    #+#             */
/*   Updated: 2024/05/03 22:38:38 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_character(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

int	find_key_idx(char *str, t_syntax *st)
{
	if (str[st->width] == '\0')
		return (FALSE);
	if (!is_white_space(str[st->width]) && !is_quote(str[st->width])
		&& !(st->width != st->word && ft_isdigit(str[st->width])))
		return (TRUE);
	return (FALSE);
}

char	*check_key(t_env_node **env_list, char *str, t_syntax *st)
{
	t_env_node	*tmp;
	char		*key;

	st->word = ++(st->width);
	if (str[st->width] == '?')
	{
		st->width++;
		return (ft_itoa(g_exit_code));
	}
	if (st->quotes == '\0' && is_quote(str[st->width]))
		return (ft_strdup(""));
	if (!is_valid_character(str[st->width]))
		return (ft_strdup("$"));
	while (find_key_idx(str, st))
		st->width++;
	key = ft_substr(str, st->word, st->width - st->word);
	tmp = is_include_env(env_list, key);
	free(key);
	if (tmp == NULL)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

char	**make_exp(t_token *new_token, t_syntax *st, int flag)
{
	int		cnt;
	char	**res;
	int		i;
	int		res_i;
	
	flag ^= 1;
	cnt = cnt_token(new_token) - flag;
	st->height += cnt;
	res = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (res == NULL)
		exit(1);
	i = flag;
	res_i = 0;
	while (new_token[i].str) 
		res[res_i++] = ft_strdup(new_token[i++].str);
	res[res_i] = NULL;
	free_tokens(new_token);
	return (res);
}

char	**get_env_value(t_env_node **env_list, char *str, char **res,
		t_syntax *st)
{
	char	*value;
	t_token	*new_token;
	char	**exp;
	int		flag;

	value = check_key(env_list, str, st);
	if (str[st->width] != '\0' && str[st->width] == st->quotes)
	{
		st->width++;
		st->quotes = '\0';
	}
	if (st->quotes == '\0' && ft_strcmp(st->sample, "export") == 0)
		res[st->height - 1] = res_join((res[st->height - 1]), value);
	else
	{
		new_token = tokenize(value);
		flag = is_white_space(value[0]);
		if (flag == FALSE)
			res[st->height - 1] = res_join((res[st->height - 1]), new_token[0].str);
		exp = make_exp(new_token, st, flag);
		res = join_exp(res, exp);
	}
	return (res);
}
