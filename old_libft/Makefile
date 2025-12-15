# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 14:08:21 by joao-alm          #+#    #+#              #
#    Updated: 2025/11/03 18:04:49 by joao-alm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
FLAGS		= -Wall -Wextra -Werror

SRC			= ft_atoi_valid.c \
			  ft_stod_valid.c \
			  ft_error.c \
			  ft_split.c ft_split_util.c\
			  gnl.c gnl_util.c \
		      int_util.c \
			  str_util.c
OBJ			= $(SRC:%.c=obj/%.o)


all: $(NAME)

obj/%.o: %.c
	mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar -rcs $@ $^
	
clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
