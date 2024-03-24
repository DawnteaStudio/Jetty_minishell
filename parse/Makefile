# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/03/24 20:36:35 by erho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
INCLUDE	= ../include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

PARSE	= test.c
EXEC	= main.c
SRCS	= $(addprefix ./, $(PARSE)) $(addprefix ../exec/, $(EXEC))
OBJS	= $(SRCS:%.c=%.o)
LIBFT	= ../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS)  -o $(NAME)

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