# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/04/08 21:26:40 by sewopark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
INCLUDE	= ../include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror 

PARSE	= test.c
EXEC	= main.c ./signal/signal.c ./builtin/pwd.c ./builtin/builtin_util.c ./builtin/env.c ./builtin/env_node.c\
			./clean/gb_cltr.c ./run/exec.c
SRCS	= $(addprefix ../parse/, $(PARSE)) $(addprefix ./, $(EXEC))
OBJS	= $(SRCS:%.c=%.o)
LIBFT	= ../libft/libft.a

TNAME = testshell
TEXEC = _main.c ./signal/signal.c ./builtin/pwd.c ./builtin/builtin_util.c ./builtin/env.c
TSRCS = $(addprefix ./, $(TEXEC))
TOBJS	= $(TSRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -lreadline -o $(NAME)

test: $(TNAME)

$(TNAME): $(TOBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(TOBJS) -lreadline -o $(TNAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(LIBFT) :
	make -C ../libft all

clean:
	make clean -C ../libft
	$(RM) $(OBJS) $(TOBJS)

fclean: clean
	make fclean -C ../libft
	$(RM) $(NAME) $(TNAME)

re:
	make fclean
	make all

tre:
	make fclean
	make test

.PHONY : all clean fclean re