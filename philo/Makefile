# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 17:20:24 by gsmereka          #+#    #+#              #
#    Updated: 2023/05/09 20:30:30 by gsmereka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo

SRC 		=	src/main.c \
				src/check_args.c \
				src/init_data.c \
				src/prepare_threads.c \
				src/finalize.c	\
				src/philosopher_routine.c \
				src/observer_routine.c \
				utils/ft_bzero.c \
				utils/ft_isdigit.c \
				utils/ft_itohex.c \
				utils/ft_putchar_fd.c \
				utils/ft_split.c \
				utils/ft_strdup.c \
				utils/ft_strlcpy.c \
				utils/ft_strncmp.c \
				utils/ft_toupper.c \
				utils/validate_int.c \
				utils/ft_calloc.c \
				utils/ft_itoa.c \
				utils/ft_putstr_fd.c \
				utils/ft_strchr.c \
				utils/ft_strjoin.c \
				utils/ft_strlen.c \
				utils/ft_substr.c \
				utils/ft_utoa.c \
				utils/ft_atoi.c \

OBJ 		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DIR		=	./obj

HEADERS 	=	./headers/philo.h ./headers/structs.h

# CCFLAGS 	=	-Wall -Wextra -Werror

THREAD_FLAG =	-pthread

RM			=	rm -f

# PHILO_ARGS (in Miliseconds)

NUMBER_OF_PHILOSOPHERS = 5
TIME_TO_DIE = 800
TIME_TO_EAT = 200
TIME_TO_SLEEP = 200
NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT = 7

PHILO_ARGS		 =	$(NUMBER_OF_PHILOSOPHERS) $(TIME_TO_DIE) \
					$(TIME_TO_EAT) $(TIME_TO_SLEEP) \
					$(NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT) \

# RULES
all: $(NAME) ascii_draw

$(OBJ_DIR)/%.o: %.c
	make create_obj_dir
	cc $(CCFLAGS) $(THREAD_FLAG) -c $< -o $@

# MANDATORY COMPILE
$(NAME): $(OBJ) $(HEADERS)
	cc $(CCFLAGS) $(THREAD_FLAG) -o $(NAME) $(OBJ) $(READLINE_FLAG)

run: $(NAME)
	clear && ./philo $(PHILO_ARGS)

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
	@mkdir -p $(OBJ_DIR)/utils

## FULL CLEAN ALL OBJECTS
git: fclean
	git add . && clear && git status

valgrind: $(NAME)
	clear && valgrind --leak-check=full --show-leak-kinds=all ./philo $(PHILO_ARGS)

.PHONY: all clean fclean re create_obj_dir git ascii_draw run
