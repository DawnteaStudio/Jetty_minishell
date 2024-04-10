/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/10 09:31:03 by sewopark         ###   ########.fr       */
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

typedef enum e_exit_code
{
	CODE_SUCCESS,
	CODE_ERROR,
	CODE_NOT_EXEC = 126,
	CODE_NOT_FOUND,
	CODE_255 = 255
}	t_exit_code;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_shell_info
{
	char			**envp;
	char			*data;//tmp
	char			**d_array;//tmp
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

//builtins
int			ft_pwd(void);
int			ft_echo(t_shell_info *shell);
int			ft_exit(t_shell_info *shell);
int			ft_env(t_shell_info *shell);
int			ft_unset(t_shell_info *shell);
int			ft_export(t_shell_info *shell);

//env
t_env_node	*is_include_env(t_env_node	**env_list, char *key);

//env_node
t_env_node	*ft_env_node_new(char *key, char *value);
void		update_env_list(t_env_node	**env_list, char *key, char *value);
void		make_env_list(t_shell_info *shell);
void		make_env_component(t_env_node **new_env_list, char *env_line);

//unset
int			is_valid_key(char *str);

//clean
char		*heap_handler(char *ptr);
void		clean_all(t_shell_info *shell);

//exec
int			ft_exec(t_shell_info *shell, char *str);

//exec_node
int			ft_exec_node(t_shell_info *shell, char *str);

//exec_builitin
int			is_builtin(char *cmd);
int			ft_exec_builtin(t_shell_info *shell, int builtin);

//exec_util
char		**ft_get_all_path(t_shell_info *shell);

#endif