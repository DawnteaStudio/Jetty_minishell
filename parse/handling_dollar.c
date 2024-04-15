/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 02:21:04 by erho              #+#    #+#             */
/*   Updated: 2024/04/16 01:27:27 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_character(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

int	find_key_idx(char *str, t_command *cmd)
{
	if (str[cmd->width] == '\0')
		return (FALSE);
	if (str[cmd->width] != ' ' && !is_quote(str[cmd->width])
		&& !(cmd->width != cmd->word && ft_isdigit(str[cmd->width])))
		return (TRUE);
	return (FALSE);
}

char	*check_key(t_env_node **env_list, char *str, t_command *cmd,
		t_tree **tree)
{
	t_env_node	*tmp;

	cmd->word = ++(cmd->width);
	if (str[cmd->width] == '?')
	{
		cmd->width++;
		return (ft_itoa(g_exit_code));
	}
	if (cmd->quotes == '\0' && is_quote(str[cmd->width]))
		return (ft_strdup(""));
	if (!is_valid_character(str[cmd->width]))
		return (ft_strdup("$"));
	while (find_key_idx(str, cmd))
		cmd->width++;
	(*tree)->env_key = ft_substr(str, cmd->word, cmd->width - cmd->word);
	(*tree)->is_env = TRUE;
	tmp = is_include_env(env_list, (*tree)->env_key);
	if (tmp == NULL)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

char	*get_env_value(char **value, char *str, char **res, t_command *cmd)
{
	char	*m_str;

	m_str = res_join(res, value);
	if (str[cmd->width] == cmd->quotes)
	{
		cmd->width++;
		cmd->quotes = '\0';
	}
	return (m_str);
}
