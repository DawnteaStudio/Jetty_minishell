/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/12 01:28:36 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
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

extern int	g_exit_code;

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

typedef enum e_token_type
{
	TOKEN_TYPE_WORD,
	TOKEN_TYPE_PIPE,
	TOKEN_TYPE_REDIRECTION,
	TOKEN_TYPE_NULL
}	t_token_type;

typedef enum e_tree_type
{
	TREE_TYPE_HEAD,
	TREE_TYPE_PHRASE,
	TREE_TYPE_COMMAND,
	TREE_TYPE_PIPE,
	TREE_TYPE_REDIRECTIONS,
	TREE_TYPE_REDIRECTION
}	t_tree_type;

typedef struct s_tree
{
	int				type;
	char			*cmd;
	char			*redir;
	char			*redir_info;
	char			**exp;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_shell_info
{
	char			**envp;
	t_tree			*tree;
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

typedef struct s_command
{
	int		word;
	int		width;
	int		height;
	char	quotes;
	int		word_count;
	int		len;
}	t_command;

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

/* ************************************************************************** */
/*************************************PARSE************************************/
/* ************************************************************************** */

// tokenizer
t_token		*tokenize(char *s, char c);

// bool_check
int			is_quote(char c);
int			is_bracket(char c);
int			is_dollar(char c);
int			is_pipe(char c);

// tokenizer_helper
int			check_sign(char *str, t_command *cmd);

// lexer
t_token		*lexical_analyze(char *str);

// parse_helper
void		free_tokens(t_token *tokens);
void		free_tree(t_tree **tree);

/* ************************************************************************** */
/*************************************EXEC*************************************/
/* ************************************************************************** */

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