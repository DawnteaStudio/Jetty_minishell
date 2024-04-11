/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/04/11 16:33:22 by erho             ###   ########.fr       */
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

typedef enum e_token_type
{
	TOKEN_TYPE_WORD,
	TOKEN_TYPE_PIPE,
	TOKEN_TYPE_REDIRECTION
}	t_token_type;

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

// tokenizer
t_token *tokenize(char *s, char c);

// bool_check
int		is_quote(char c);
int		is_bracket(char c);
int		is_dollar(char c);
int		is_pipe(char c);

// tokenizer_helper
int 	check_sign(char *str, t_command *cmd);

// lexer
t_token	*lexical_analyze(char *str);

/* ************************************************************************** */
/*************************************EXEC*************************************/
/* ************************************************************************** */

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

#endif