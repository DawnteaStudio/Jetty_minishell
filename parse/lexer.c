/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:34:57 by erho              #+#    #+#             */
/*   Updated: 2024/04/08 20:34:58 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int cnt_token(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens[i].str)
		i++;
	return (i);
}

void	check_quote(char *str)
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
				exit(1);
		}
		i++;
	}
}

int check_str(char *str)
{
	if (is_bracket(str[0]))
		return (TYPE_REDIRECT);
	if (is_pipe(str[0]))
		return (TYPE_PIPE);
	check_quote(str);
	return (TYPE_WORD);
}

t_token	*lexical_analyze(char *str)
{
	int		cnt;
	int 	i;
	t_token *tokens;

	tokens = tokenize(str, ' ');
	cnt = cnt_token(tokens);
	if (cnt == 0)
		exit(1);
	i = 0;
	while (i < cnt)
	{
		tokens[i].type = check_str(tokens[i].str);
		i++;
	}
	return (tokens);
}