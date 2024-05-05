/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/05 14:22:57 by erho             ###   ########.fr       */
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

# define FALSE		0
# define TRUE		1
# define ADDBACK	2

# define DEFAULT	0
# define IGNORE		1
# define CUSTOM		2
# define CHSIGINT	3
# define HDSIGINT	4

# define DIRLEFT	0
# define DIRRIGT	1

# define K_UNSET	0
# define K_EXPRT	1

# define ENV_PATH	"/usr/local/bin:/usr/bin:/bin:\
/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Library/Frameworks/\
Mono.framework/Versions/Current/Commands"

extern int	g_exit_code;

typedef enum e_builtin
{
	BLT_ECHO = 1,
	BLT_CD,
	BLT_PWD,
	BLT_EXPORT,
	BLT_UNSET,
	BLT_ENV,
	BLT_EXIT,
	BLT_NULL
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
	TREE_TYPE_PHRASE,
	TREE_TYPE_COMMAND,
	TREE_TYPE_PIPE,
	TREE_TYPE_REDIRECTIONS,
	TREE_TYPE_REDIRECTION
}	t_tree_type;

typedef enum e_error_type
{
	ERR_CMD_NOT_FND,
	ERR_NO_SUCH_FILE,
	ERR_PER_DENIED,
	ERR_AMBIGUOUS,
	ERR_PERROR
}	t_error_type;

typedef struct s_tree
{
	int				type;
	char			*cmd;
	char			*redir;
	char			**redir_info;
	char			**exp;
	char			*tmp_file;
	char			*origin_token;
	int				here_doc;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_backup
{
	char	*pwd;
	char	*shlvl;
}	t_backup;

typedef struct s_shell_info
{
	char			*backup_pwd;
	char			*backup_oldpwd;
	char			**envp;
	char			**env;
	t_tree			*tree;
	int				backup_stdin;
	int				backup_stdout;
	int				pure_oldpwd;
	int				cd_before;
	int				heredoc_quit;
	int				origin;
	int				path_avil;
	struct termios	term;
	t_env_node		*env_list;
	t_backup		*backup_pocket;
}	t_shell_info;

typedef struct s_component
{
	char		*key;
	char		*value;
	int			flag_check_value;
	size_t		i;
	size_t		len;
	t_env_node	*check;
	t_env_node	**new_env_list;
}	t_component;

typedef struct s_syntax
{
	int		word;
	int		width;
	int		height;
	char	quotes;
	int		word_count;
	int		len;
	char	q_back_up;
	char	*sample;
}	t_syntax;

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

/* ************************************************************************** */
/*************************************PARSE************************************/
/* ************************************************************************** */

// tokenizer
t_token		*tokenize(char *s);

// bool_check
int			is_quote(char c);
int			is_bracket(char c);
int			is_dollar(char c);
int			is_pipe(char c);
int			is_white_space(char c);

// tokenizer_helper
int			check_sign(char *str, t_syntax *st);

// lexer
t_token		*lexical_analyze(char *str);
int			cnt_token(t_token *tokens);

// parse_helper
void		free_tokens(t_token *tokens);
void		free_tree(t_tree **tree);
int			cnt_exp(char **exp);

// parse
t_tree		*parse(char *str, t_env_node **env_list);

// set_tree_utils
char		*res_join(char *str, char *temp);
void		tree_find_idx(char *str, t_syntax *st);
void		tree_make_word(char *s1, char *s2, t_syntax st);
char		**set_exp();
char		**join_exp_n_str(char **exp, char **str);

// set_tree
t_tree		*create_node(int type);
char		**extract_data(char *str, char *cmd, t_env_node **env_list);

// handling_dollar
char		**get_env_value(t_env_node **env_list, char *str, char **res,
				t_syntax *st);

// insert_tree
int			pipe_node(t_tree **tree, t_token *tokens, t_env_node **env_list,
				int idx);

// insert_tree_util
char		**join_exp(char **tree_exp, char **tmp);
t_tree		*find_last_right(t_tree *tree);
void		cpy_new_exp(char **new_exp, char **exp, char **tmp);

// test
t_env_node	*create_list(char *key, char *value);
t_env_node	*is_include_env(t_env_node **env_list, char *key);

/* ************************************************************************** */
/*************************************EXEC*************************************/
/* ************************************************************************** */

//signal
void		signal_handler(int num);
void		set_signal(int sig_int, int sig_quit);

//builtins
int			ft_pwd(void);
int			ft_echo(t_tree *tree);
int			ft_exit(t_shell_info *shell, t_tree *tree);
int			ft_env(t_shell_info *shell);
int			ft_unset(t_shell_info *shell, t_tree *tree);
int			ft_export(t_shell_info *shell, t_tree *tree);
int			ft_cd(t_shell_info *shell, t_tree *tree);

//env
t_env_node	*is_include_env(t_env_node	**env_list, char *key);
t_backup	*make_backup_env(void);
void		make_new_envp_helper(t_shell_info *shell, t_env_node *list, int *i);

//export
void		ft_check_backup_pwd(t_shell_info *shell);

//env_node
t_env_node	*ft_env_node_new(char *key, char *value);
void		update_env_list(t_env_node	**env_list, char *key, char *value);
void		make_env_list(t_shell_info *shell);
void		make_env_component(t_env_node **new_env_list, char *env_line);

//pwd
void		ft_pwds_helper(t_shell_info *shell, char *key);
int			ft_change_pwd(t_shell_info *shell);

//unset
int			is_valid_key(char *str, int check);
void		unset(t_shell_info *shell, char *key);

//clean
char		*heap_handler(char *ptr);
void		clean_all(t_shell_info *shell);
void		del(char *ptr);

//exec
int			ft_exec(t_shell_info *shell, t_tree *tree);
void		ft_exec_preprocess(t_shell_info *shell, t_tree *tree);

//exec_node
int			ft_exec_node(t_shell_info *shell, t_tree *tree);

//exec_builitin
int			is_builtin(char *cmd);
int			ft_exec_builtin(t_shell_info *shell, t_tree *tree, int builtin);

//exec_redirection
int			ft_exec_redirection(t_tree *tree);
void		ft_here_doc(t_shell_info *shell, t_tree *tree);
int			ft_add_redirection(t_tree *redirs);

//exec_util
char		**ft_get_all_path(t_shell_info *shell);
int			ft_close_and_wait(int *status, int fd[2], pid_t pid_right);
int			ft_exit_status(int status);
int			ft_restore_fd(t_shell_info *shell, int status);
int			ft_get_len(t_env_node *list);

//exec_access
t_exit_code	is_read(char *file);
t_exit_code	is_write(char *file);

//exec_error
t_exit_code	putstr_error(char *str, t_exit_code code, t_error_type type);
int			null_amb(char *str);

#endif