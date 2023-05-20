# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 12:22:49 by mrezaei           #+#    #+#              #
#    Updated: 2023/05/20 12:45:30 by mrezaei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = -Wall -Wextra -Werror
OPTION = -pthread

TARGET = philo

SRC = main.c init.c behavior.c utils.c ft_init.c
OBJ = $(SRC:.c=.o)

$(NAME) : all

all : $(TARGET)

$(TARGET) : $(OBJ)
	      $(CC) $(CFLAG) -o $(TARGET) $(OBJ) $(OPTION)

$(OBJ) : $(SRC)
	   $(CC) $(CFLAG) -c $(SRC) $(OPTION)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(TARGET)

re : fclean all

.PHONY : clean fclean all re
