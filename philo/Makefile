# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mekundur <mekundur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 19:21:49 by mekundur          #+#    #+#              #
#    Updated: 2025/02/11 23:42:11 by mekundur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo	
HEADER = src/philo.h
SRC = main.c init.c input.c monitor.c philo.c routine_multi.c routine_one.c utils.c
SRC := $(addprefix src/, $(SRC))

OBJECTS = $(SRC:.c=.o)

all : $(NAME) 

%.o: %.c Makefile 
	@cc -c -g -Werror -Wall -Wextra $< -o $@ 

$(NAME) : $(HEADER) $(OBJECTS) Makefile
	@echo "Creating the program <philo>"
#	@cc -g -g -Werror -Wall -Wextra -fsanitize=address $(OBJECTS) -o $(NAME)
#	@cc -g -g -Werror -Wall -Wextra -fsanitize=thread $(OBJECTS) -o $(NAME)
	@cc -g -Werror -Wall -Wextra $(OBJECTS) -o $(NAME)

clean :
	@echo "Removing object files"
	@rm -f $(OBJECTS)

fclean : clean 
	@echo "Removing the executable <philo>"
	@rm -f philo

re : fclean all

.PHONY: all, clean, fclean, re
