# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/08 16:51:43 by vbrovenk          #+#    #+#              #
#    Updated: 2018/07/08 16:51:45 by vbrovenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vbrovenk.filler
INC_DIR = ./libft/includes/
SRC = main.c manhattan.c create.c get_sizes.c determine_coord.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
OFF=\033[0m

RED=\033[31m
REDBOLD=\033[1;31m
GREEN=\033[32m
GREENBOLD=\033[1;32m
YELLOW=\033[33m
YELLOWBOLD=\033[1;33m
PURPLE=\033[35m
PURPLEBOLD=\033[1;35m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(PURPLEBOLD)Filler is ready.$(OFF)"

%.o: %.c
	@gcc -c $< -o $@ -I $(INC_DIR)

clean:
	rm -rf $(OBJ)
	@make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft/

re: fclean all