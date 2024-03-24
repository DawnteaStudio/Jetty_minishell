/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:05 by sewopark          #+#    #+#             */
/*   Updated: 2024/03/24 18:10:32 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*str;

	((void)argc, (void)argv, (void)envp);
	while (1)
	{
		str = readline("jetty_shell>");
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
