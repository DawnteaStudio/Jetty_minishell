/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 03:15:19 by parksewon         #+#    #+#             */
/*   Updated: 2024/05/08 20:39:52 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	find_end_index(char *line, size_t i)
{
	while (line[i])
	{
		if (line[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

size_t	find_here_doc_key(char *line, size_t i, size_t *start)
{
	size_t	pure;

	pure = *start;
	while (line[i])
	{
		if (ft_isalpha(line[i]) == TRUE || line[i] == '_')
		{
			if (pure == *start)
				(*start)++;
			i++;
		}
		else if (ft_isdigit(line[i]) == TRUE)
		{
			i++;
			if (line[i - 1] == '$')
				return (i);
		}
		else
			break ;
	}
	return (i);
}

void	expand_dollar(t_shell_info *shell, int fd, size_t *start, size_t *end)
{
	t_env_node	*node;
	char		*tmp;

	*end = find_here_doc_key(shell->here_doc, (*start) + 1, start);
	tmp = ft_substr(shell->here_doc, *start, (*end) - (*start));
	node = is_include_env(&shell->env_list, tmp);
	if (node)
	{
		if (node->value)
			ft_putstr_fd(node->value, fd);
	}
	else if (ft_isalpha(tmp[0]) != TRUE && tmp[0] != '_')
		ft_putstr_fd(tmp, fd);
	*start = *end;
	del(&tmp);
}

void	expand_no_dollar(t_shell_info *shell, int fd, size_t *s, size_t *e)
{
	char	*tmp;

	*e = find_end_index(shell->here_doc, *e);
	tmp = ft_substr(shell->here_doc, *s, *e - *s);
	*s = *e;
	ft_putstr_fd(tmp, fd);
	del(&tmp);
}

void	write_loop(t_shell_info *shell, int fd, size_t *start, size_t *end)
{
	size_t	len;

	len = ft_strlen(shell->here_doc);
	while (*end < len)
	{
		if (shell->here_doc[*start] == '$')
			expand_dollar(shell, fd, start, end);
		else
			expand_no_dollar(shell, fd, start, end);
	}
}
