/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/04 15:31:39 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>

/* ************************************************************************** */
/*************************************PARSE************************************/
/* ************************************************************************** */

/* ************************************************************************** */
/*************************************EXEC*************************************/
/* ************************************************************************** */

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>

# define TRUE		1
# define FALSE		0

# define DEFAULT	0
# define IGNORE		1
# define CUSTOM		2

typedef struct s_shell_info
{
	char		**envp;
	int			backup_stdin;
	int			backup_stdout;
	t_env_node	*env_list;
}	t_shell_info;

typedef struct s_env_node
{
	char		*key;
	char		*value;
	t_env_node	*next;
}	t_env_node;

//signal
void		signal_handler(int num);
void		set_signal(int sig_int, int sig_quit);

//**built_in**
int			is_builtin(char *cmd);

//pwd
int			ft_pwd(void);

//env
t_env_node	*make_env_list(char **envp);

#endif