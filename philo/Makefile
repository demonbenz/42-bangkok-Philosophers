# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otangkab <otangkab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/25 21:21:30 by otangkab          #+#    #+#              #
#    Updated: 2023/04/20 00:47:53 by otangkab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo

SRCS		:=	philo.c philo_utils.c philo_actions.c philo_died.c philo_creates.c

CC		:=	gcc
CFLAGS		:=	-g -Wall -Wextra -Werror
OBJS		:=	$(SRCS:.c=.o)


all:	$(NAME)

$(NAME):	$(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all re fclean clean
