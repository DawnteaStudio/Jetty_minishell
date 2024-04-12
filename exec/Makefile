# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/04/11 21:07:53 by sewopark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
INCLUDE	= ../include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror 

BUILTIN	= echo.c env_node.c env.c exit.c pwd.c unset.c export.c
RUN		= exec_builtin.c exec_node.c exec_redirect.c exec_util.c exec.c
EXEC	= main.c signal/signal.c $(addprefix builtin/, $(BUILTIN)) $(addprefix run/, $(RUN)) clean/gb_cltr.c

SRCS	= $(addprefix ./, $(EXEC))
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