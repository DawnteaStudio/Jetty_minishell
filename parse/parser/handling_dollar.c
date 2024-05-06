/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 02:21:04 by erho              #+#    #+#             */
/*   Updated: 2024/05/06 17:32:46 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_height(char **res, char *value, t_syntax *st)
{
	int	last;

	st->height = cnt_exp(res) - 1;
	last = (int)ft_strlen(value) - 1;
	if (is_white_space(value[last]) == TRUE)
		st->height++;
}

int	find_key_idx(char *str, t_syntax *st)
{
	if (str[st->width] == '\0')
		return (FALSE);
	if (is_white_space(str[st->width]) || is_quote(str[st->width]))
		return (FALSE);
	if (st->width == st->word && ft_isdigit(str[st->width]))
		return (FALSE);
	if (str[st->width] == '$')
		return (FALSE);
	return (TRUE);
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
	if (!(ft_isalpha(str[st->width]) || ft_isdigit(str[st->width])
			|| str[st->width] == '_'))
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

char	**get_env_value(t_env_node **env_list, char *str, char **res,
		t_syntax *st)
{
	char	*value;
	t_token	*new_token;
	char	**exp;
	int		flag;

	value = check_key(env_list, str, st);
	if (st->quotes != '\0' || ft_strcmp(st->sample, "export") == 0)
		res[st->height] = str_join((res[st->height]), value);
	else
	{
		new_token = tokenize(value);
		flag = is_white_space(value[0]);
		if (flag == TRUE && res[st->height][0] != '\0')
			st->height++;
		exp = make_exp(new_token);
		res = join_exp(res, exp, st->height);
		set_height(res, value, st);
	}
	if (str[st->width] != '\0' && str[st->width] == st->quotes)
	{
		st->width++;
		st->quotes = '\0';
	}
	free(value);
	return (res);
}
