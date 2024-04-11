# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/04/11 21:46:17 by erho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
INCLUDE	= ../include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

PARSE	= _test_main.c tokenizer.c tokenizer_helper.c bool_check.c lexer.c \
			parse_helper.c
SRCS	= $(PARSE)
OBJS	= $(SRCS:%.c=%.o)
LIBFT	= ../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -lreadline -o $(NAME)

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
