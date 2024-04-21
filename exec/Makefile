# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/04/22 03:10:39 by parksewon        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME	= minishell
# INCLUDE	= ../include/
# CC		= gcc
# RM		= rm -f
# CFLAGS	= -Wall -Wextra -Werror

# BUILTIN	= echo.c env_node.c env.c exit.c pwd.c unset.c export.c cd.c
# RUN		= exec_builtin.c exec_node.c exec_redirect.c exec_util.c exec.c exec_access.c\
# exec_error.c
# EXEC	= main.c signal/signal.c $(addprefix builtin/, $(BUILTIN)) $(addprefix run/, $(RUN)) clean/gb_cltr.c
# PARSE	= tokenizer.c tokenizer_helper.c bool_check.c lexer.c \
# 			parse_helper.c handling_dollar.c parser.c set_tree_utils.c \
# 			set_tree.c insert_tree.c insert_tree_utils.c

# SRCS	= $(addprefix ./, $(EXEC)) $(addprefix ../parse/, $(PARSE))
# OBJS	= $(SRCS:%.c=%.o)
# LIBFT	= ../libft/libft.a

# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -lreadline -o $(NAME)

# %.o : %.c
# 	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

# $(LIBFT) :
# 	make -C ../libft all

# clean:
# 	make clean -C ../libft
# 	$(RM) $(OBJS)

# fclean: clean
# 	make fclean -C ../libft
# 	$(RM) $(NAME)

# re:
# 	make fclean
# 	make all

# .PHONY : all clean fclean re

NAME	= minishell
INCLUDE	= ../include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS	= -L/usr/local/opt/readline/lib
LDLIBS	= -lreadline
BUILTIN	= echo.c env_node.c env.c exit.c pwd.c unset.c export.c cd.c
RUN		= exec_builtin.c exec_node.c exec_redirect.c exec_util.c exec.c exec_access.c\
exec_error.c exec_heredoc.c
EXEC	= main.c signal/signal.c $(addprefix builtin/, $(BUILTIN)) $(addprefix run/, $(RUN)) clean/gb_cltr.c
PARSE	= tokenizer.c tokenizer_helper.c bool_check.c lexer.c \
			parse_helper.c handling_dollar.c parser.c set_tree_utils.c \
			set_tree.c insert_tree.c insert_tree_utils.c

SRCS	= $(addprefix ./, $(EXEC)) $(addprefix ../parse/, $(PARSE))
OBJS	= $(SRCS:%.c=%.o)
LIBFT	= ../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(LIBFT) :
	make -C ../libft all

clean:
	make clean -C ../libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ../libft
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY : all clean fclean re
