# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 09:31:40 by eabdelha          #+#    #+#              #
#    Updated: 2022/03/21 09:31:42 by eabdelha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FOBJ_SRC = object_files
OBJECT_PATH = ./object_files/

INCLUDE = philo.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC	=	philo.c		\
		utils.c		\
		create_pthreads.c	\
		checks.c


OBJECTS = $(addprefix $(OBJECT_PATH), $(SRC:.c=.o))

.PHONY : all clean fclean re

$(NAME): $(FOBJ_SRC) $(OBJECTS)
	@$(CC)  $(CFLAGS) $(OBJECTS) -o $(NAME) -pthread

$(OBJECT_PATH)%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(FOBJ_SRC) : 
	@mkdir $@

clean:
	@rm -f $(OBJECTS)
	@rm -rf $(FOBJ_SRC)

fclean: clean
	@rm -f $(NAME)

re: fclean all