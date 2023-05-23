# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 12:22:49 by mrezaei           #+#    #+#              #
#    Updated: 2023/05/23 18:11:57 by mrezaei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
CFLAGS 		=	-Wall -Wextra -Werror
OPTION 		=	-pthread
NAME 		=	philosophers
CFILES		=	$(shell find ./src -name "*.c" -type f)
OBJECTS		=	$(CFILES:.c=.o)

Y	= "\033[33m"
R	= "\033[31m"
G	= "\033[32m"
B	= "\033[34m"
X	= "\033[0m"
UP	= "\033[A"
CUT	= "\033[K"

all : $(NAME)

$(NAME) : $(OBJECTS)
	      $(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(OPTION)
	@echo $(G)==================================$(X)
	@echo $(G)Compiled Successfully
	@echo $(G)The output file is [$(NAME)]$(X)
	@echo $(G)==================================$(X)
	@echo

$(OBJECTS) : %.o : %.c
	@echo $(Y)Compiling [$<]...$(X)
	$(CC) $(CFLAGS) -c $< -o $@ $(OPTION)

clean:
	rm -rf $(OBJECTS)
	@echo $(R)Removed [$(OBJECTS)]$(X)

fclean: clean
	rm -rf $(NAME)
	@echo $(R)Removed [$(NAME)]$(X)

re : fclean all

norm:
	@echo $(G)Norminette cheking...
	@echo
	norminette src includes

.PHONY : clean fclean all re norm
