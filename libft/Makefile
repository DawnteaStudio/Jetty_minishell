# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/17 15:59:02 by erho              #+#    #+#              #
#    Updated: 2024/04/05 14:14:46 by sewopark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_putchar.c ft_putstr.c ft_split.c \
		ft_strlcat.c ft_strlen.c ft_strcmp.c\
		ft_putstr_fd.c ft_strdup.c ft_strjoin.c ft_error.c ft_strncmp.c\
		ft_memset.c ft_lst.c ft_strlcpy.c ft_substr.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
HDIR = includes

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o : %.c
	cc $(CFLAGS) -c $< -o $@ -I${HDIR}

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
