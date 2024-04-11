/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 02:21:04 by erho              #+#    #+#             */
/*   Updated: 2024/04/10 04:10:37 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_key(t_env_node **env_list, char *str, t_command *cmd)
{
	char		*key;
	t_env_node	*tmp;

	if (str[cmd->width] == ' ' || str[cmd->width] == '\0')
		return (ft_strdup("$"));
	if (is_quote(str[cmd->width]))
		return (ft_strdup(""));
	while (str[cmd->width] && str[cmd->width] != ' '
		&& !is_quote(str[cmd->width]))
		cmd->width++;
	key = ft_substr(str, cmd->word, cmd->width - cmd->word);
	tmp = is_include_env(env_list, key);
	if (tmp == NULL)
		return (ft_strdup(""));
	free(key);
	return (ft_strdup(tmp->value));
}

char	*get_env_value(t_env_node **env_list, char *str, char **res,
		t_command *cmd)
{
	char	*value;
	char	*m_str;

	cmd->word = ++(cmd->width);
	value = check_key(env_list, str, cmd);
	m_str = res_join(res, &value);
	if (str[cmd->width] == cmd->quotes)
	{
		cmd->width++;
		cmd->quotes = '\0';
	}
	return (m_str);
}
