
NAME = philo	
HEADER = src/philo.h
SRC = main.c input.c monitor.c philo.c routine_multi.c routine_one.c utils.c
SRC := $(addprefix src/, $(SRC))

OBJECTS = $(SRC:.c=.o)

all : $(NAME) 

%.o: %.c Makefile 
	@cc -c -g -Werror -Wall -Wextra $< -o $@ 

$(NAME) : $(HEADER) $(OBJECTS) Makefile
	@echo "Creating the program <philo>"
#	@cc -g -g -Werror -Wall -Wextra -fsanitize=address $(OBJECTS) -o $(NAME)
#	@cc -g -g -Werror -Wall -Wextra -fsanitize=thread $(OBJECTS) -o $(NAME)
#	@cc -c -g -fsanitize=address -Werror -Wall -Wextra $(OBJECTS) -o $(NAME)
	@cc -g -Werror -Wall -Wextra $(OBJECTS) -o $(NAME)

clean :
	@echo "Removing object files"
	@rm -f $(OBJECTS)

fclean : clean 
	@echo "Removing the executable <philo>"
	@rm -f philo

re : fclean all

.PHONY: all, clean, fclean, re
