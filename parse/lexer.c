/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:34:57 by erho              #+#    #+#             */
/*   Updated: 2024/04/11 22:42:52 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cnt_token(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].str)
		i++;
	return (i);
}

int	check_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && (!is_quote(str[i]) || str[i] != quote))
				i++;
			if (!str[i])
				return (CODE_ERROR);
		}
		i++;
	}
	return (CODE_SUCCESS);
}

int	check_str(char *str)
{
	if (is_bracket(str[0]))
		return (TOKEN_TYPE_REDIRECTION);
	if (is_pipe(str[0]))
		return (TOKEN_TYPE_PIPE);
	if (check_quote(str) == CODE_ERROR)
		return (-1);
	return (TOKEN_TYPE_WORD);
}

t_token	*lexical_analyze(char *str)
{
	int		cnt;
	int		i;
	t_token	*tokens;

	tokens = tokenize(str, ' ');
	cnt = cnt_token(tokens);
	i = 0;
	while (i < cnt)
	{
		tokens[i].type = check_str(tokens[i].str);
		if (tokens[i].type == -1)
		{
			free_tokens(tokens);
			return (NULL);
		}
		i++;
	}
	return (tokens);
}
