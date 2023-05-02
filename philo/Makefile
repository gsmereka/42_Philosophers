# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 17:20:24 by gsmereka          #+#    #+#              #
#    Updated: 2023/05/02 17:47:13 by gsmereka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	philo

SRC 	=	src/main.c \

OBJ 	=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DIR	=	./obj

# PARAMETERS

NUMBER_OF_PHILOSOPHERS = 1
TIME_TO_DIE = 1
TIME_TO_EAT = 1
TIME_TO_SLEEP = 1
NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT = 1
PARAMETERS = $(NUMBER_OF_PHILOSOPHERS) $(TIME_TO_DIE) $(TIME_TO_EAT) $(TIME_TO_SLEEP) $(NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT)

# MAKEFILE UTILS 

HEADERS =	./headers/philo.h ./headers/structs.h

CCFLAGS =	-Wall -Wextra -Werror

RM		=	rm -f

# RULES
all: $(NAME) ascii_draw

$(OBJ_DIR)/%.o: %.c
	make create_obj_dir
	cc $(CCFLAGS) -c $< -o $@

# MANDATORY COMPILE
$(NAME): $(OBJ) $(HEADERS) $(LIBFT_A)
	cc $(CCFLAGS) -o $(NAME) $(OBJ) $(READLINE_FLAG)

exec: $(NAME)
	./philo

ascii_draw:
	@echo "\033[1;35m"
	@echo "░░┌──┐░░░░░░░░░░┌──┐░░░░░░┌──┐░░░░░░░░░░┌──┐░░░░░░┌──┐░░░░░░░░░░┌──┐░░"
	@echo "░╔╡▐▐╞╝░░┌──┐░░╔╡▐▐╞╝░░░░╔╡▐▐╞╝░░┌──┐░░╔╡▐▐╞╝░░░░╔╡▐▐╞╝░░┌──┐░░╔╡▐▐╞╝░"
	@echo "░░└╥╥┘░░╚╡▌▌╞╗░░└╥╥┘░░░░░░└╥╥┘░░╚╡▌▌╞╗░░└╥╥┘░░░░░░└╥╥┘░░╚╡▌▌╞╗░░└╥╥┘░░"
	@echo "░░░╚╚░░░░└╥╥┘░░░░╚╚░░░░░░░░╚╚░░░░└╥╥┘░░░░╚╚░░░░░░░░╚╚░░░░└╥╥┘░░░░╚╚░░░"
	@echo "░░░░░░░░░░╝╝░░░░░░░░░░░░░░░░░░░░░░╝╝░░░░░░░░░░░░░░░░░░░░░░╝╝░░░░░░░░░░"
	@echo "\033[0m"

# RULES CLEAN FCLEAN AND RE
clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_A)

re: fclean all

# CREATE OBJECTS DIR
create_obj_dir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src

## FULL CLEAN ALL OBJECTS
git: fclean
	git add . && clear && git status

valgrind: $(NAME)
	valgrind --suppressions=$$PWD/tester/readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes ./philo

.PHONY: all clean fclean re create_obj_dir git ascii_draw exec
