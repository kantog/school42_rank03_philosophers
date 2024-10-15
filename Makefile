# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 11:00:50 by bclaeys           #+#    #+#              #
#    Updated: 2024/09/26 16:24:47 by bclaeys          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo
CFILES=src/phil_main.c src/phil_utils.c src/phil_init.c src/phil_routine.c \
	   src/phil_free_exit.c 
CFILES_PRINTF=src/ft_printf/ft_printf.c \
		src/ft_printf/ft_format.c src/ft_printf/ftpr_puthex.c \
		src/ft_printf/ftpr_putchar.c src/ft_printf/ftpr_putint.c \
		src/ft_printf/ftpr_putptr.c src/ft_printf/ftpr_putunsdec.c \
		src/ft_printf/ftpr_putstr.c \
  
CC=cc
PROJECT_FLAGS= -pthread
CFLAGS= -Wall -Wextra -Werror -g
PRINTF_OBJECTS=$(patsubst src/ft_printf/%.c,obj/ft_printf/%.o,$(CFILES_PRINTF))
OBJECTS=$(patsubst src/%.c,obj/%.o,$(CFILES))

# MAKE_COMPILE_JSON = $(CC) -MJ compile_commands.json

all: obj $(NAME)
	@(make -q $(NAME) && echo "Everything up to date") || (make  build)
	
$(NAME): $(PRINTF_OBJECTS) $(OBJECTS) 
	$(CC) $(PROJECT_FLAGS) $(CFLAGS) -o $(NAME) $(OBJECTS) $(PRINTF_OBJECTS)
	find ./obj/ -type f -name "*.json" | xargs sed -e '1s/^/[\n/' -e '$$s/,$$/\n]/' > compile_commands.json
	@echo "\033[33mphilo created\033[0m"

obj: 
	@mkdir -p obj
	@mkdir -p obj/ft_printf 

obj/ft_printf/%.o: src/ft_printf/%.c
	$(CC) $(PROJECT_FLAGS) $(CFLAGS) -MJ $@.json -c -o $@ $<

obj/%.o: src/%.c
	$(CC) $(PROJECT_FLAGS) $(CFLAGS) -MJ $@.json -c -o $@ $<

clean:
	@rm -rf obj
	@if [ -d "obj" ]; then rmdir obj/; \
	fi
	@echo "\033[33mAll object files, dependency files, archive files and test files removed.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[33mBinary removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re obj 
