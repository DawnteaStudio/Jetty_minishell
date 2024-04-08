/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/08 21:23:58 by sewopark         ###   ########.fr       */
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

extern int	g_exit_code;

# define TRUE		1
# define FALSE		0

# define DEFAULT	0
# define IGNORE		1
# define CUSTOM		2

typedef enum e_builtin
{
	BLT_ECHO = 1,
	BLT_CD,
	BLT_PWD,
	BLT_EXPORT,
	BLT_UNSET,
	BLT_ENV,
	BLT_EXIT
}	t_builtin;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_shell_info
{
	char			**envp;
	int				backup_stdin;
	int				backup_stdout;
	struct termios	term;
	t_env_node		*env_list;
}	t_shell_info;

typedef struct s_component
{
	char		*key;
	char		*value;
	int			flag_check_value;
	size_t		i;
	size_t		len;
	t_env_node	*tmp;
}	t_component;

//signal
void		signal_handler(int num);
void		set_signal(int sig_int, int sig_quit);

//**built_in**
int			is_builtin(char *cmd);

//pwd
int			ft_pwd(void);

//env
t_env_node	*is_include_env(t_env_node	**env_list, char *key);
int			ft_env(t_shell_info *shell);

//env_node
t_env_node	*ft_env_node_new(char *key, char *value);
void		update_env_list(t_env_node	**env_list, char *key, char *value);
void		make_env_list(t_shell_info *shell);

//clean
char		*heap_handler(char *ptr);
void		clean_all(t_shell_info *shell);

//exec
int			ft_exec(t_shell_info *shell, char *str);

#endif