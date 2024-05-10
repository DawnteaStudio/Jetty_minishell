/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 02:21:04 by erho              #+#    #+#             */
/*   Updated: 2024/05/10 15:03:01 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_quote(char *str, t_syntax *st)
{
	if (str[st->width] != '\0' && str[st->width] == st->quotes)
	{
		st->width++;
		st->quotes = '\0';
	}
}

void	set_height(char **res, char *value, t_syntax *st)
{
	int	last;

	st->height = cnt_exp(res) - 1;
	last = (int)ft_strlen(value) - 1;
	if (value[0] && is_white_space(value[last]) == TRUE)
		st->height++;
}

int	find_key_idx(char *str, t_syntax *st)
{
	if (str[st->width] == '\0')
		return (FALSE);
	if (is_white_space(str[st->width]) || is_quote(str[st->width]))
		return (FALSE);
	if (str[st->width] == '$' || str[st->width] == '/')
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
	if (!(ft_isalpha(str[st->width]) || str[st->width] == '_')
		|| ft_strcmp(st->sample, "<<") == 0)
		return (ft_strdup("$"));
	while (find_key_idx(str, st))
		st->width++;
	key = ft_substr(str, st->word, st->width - st->word);
	tmp = is_include_env(env_list, key);
	free(key);
	if (tmp == NULL || tmp->value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

char	**get_env_value(t_env_node **env_list, char *str, char **res,
		t_syntax *st)
{
	char	*value;
	t_token	*new_token;
	char	**exp;

	value = check_key(env_list, str, st);
	if (st->quotes != '\0' || ft_strcmp(st->sample, "export") == 0)
		res[st->height] = str_join((res[st->height]), value);
	else
	{
		new_token = tokenize(value);
		if (new_token[0].str == NULL)
		{
			free_tokens(new_token);
			free(value);
			return (res);
		}
		if (is_white_space(value[0]) && (res[st->height] && res[st->height][0]))
			st->height++;
		exp = make_exp(new_token);
		res = join_exp(res, exp, st->height);
		set_height(res, value, st);
	}
	set_quote(str, st);
	free(value);
	return (res);
}
