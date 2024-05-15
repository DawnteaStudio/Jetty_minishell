# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/05/10 15:14:50 by sewopark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
INCLUDE	= include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
LDLIBS	= -lreadline
BUILTIN	= echo.c env_node.c env.c exit.c pwd.c unset.c export.c cd.c null.c
RUN		= exec_builtin.c exec_node.c exec_redirect.c exec_util.c exec.c exec_access.c\
exec_error.c exec_heredoc.c exec_heredoc_util.c
EXEC	= main.c signal/signal.c $(addprefix builtin/, $(BUILTIN)) $(addprefix run/, $(RUN)) clean/gb_cltr.c
LEXER	= lexer/lexer.c
PARSER	= parser/handling_dollar.c parser/parser.c parser/set_tree_utils.c \
			parser/set_tree.c parser/insert_tree.c parser/insert_tree_utils.c \
			parser/join.c
TOKEN	= tokenizer/tokenizer.c tokenizer/tokenizer_utils.c
PARSE	= bool_check.c free.c $(LEXER) $(PARSER) $(TOKEN) $(TEST)

SRCS	= $(addprefix exec/, $(EXEC)) $(addprefix parse/, $(PARSE))
OBJS	= $(SRCS:%.c=%.o)
LIBFT	= ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(LIBFT) :
	make -C libft all

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY : all clean fclean re
