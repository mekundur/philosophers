
NAME = philo	
HEADER = src/philo.h
SRC = main.c philo.c routine.c utils.c
SRC := $(addprefix src/, $(SRC))

OBJECTS = $(SRC:.c=.o)

all : $(NAME) 

%.o: %.c Makefile 
	@cc -c -g -lpthread -Werror -Wall -Wextra $< -o $@ 
#	@cc -c -g -fsanitize=address -lpthread -Werror -Wall -Wextra $< -o $@ 

$(NAME) : $(HEADER) $(OBJECTS) Makefile
	@echo "Creating the program <philo>"
	@cc -g -Werror -Wall -Wextra $(OBJECTS) -o $(NAME)

clean :
	@echo "Removing object files"
	@rm -f $(OBJECTS)

fclean : clean 
	@echo "Removing the executable <philo>"
	@rm -f philo

re : fclean all

.PHONY: all, clean, fclean, re
