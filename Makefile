# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 14:08:21 by joao-alm          #+#    #+#              #
#    Updated: 2025/11/05 23:02:01 by joao-alm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
BNAME	= miniRT_bonus

CC		= cc
FLAGS	= -Wall -Wextra -Werror \
		  -O3 -march=native -ffast-math \
		  -Wno-incompatible-pointer-types

# libs
MLX		= lib/mlx/libmlx.a
MLXINC	= -I lib/mlx
MLXL	= -Llib/mlx -lmlx -lXext -lX11 -lm

LIBFT	= lib/libft/libft.a
LIBFTIN	= -I lib/libft
LIBFTL	= -Llib/libft -lft

# mandatory files
MINC	= -I mandatory/inc
MSRC	= main.c

MPARSER	= parser.c \
		  parse_elements.c \
		  parse_objects.c \
		  parse_objects_utils.c \
		  parse_utils.c \
		  parse_validation.c
MPARSER	:= $(addprefix parser/, $(MPARSER))

MRENDER	= render.c \
		  find_closest_hit.c \
		  cylinder/hit_cylinder.c \
		  cylinder/intersect_cylinder.c \
		  plane/hit_plane.c \
		  plane/intersect_plane.c \
		  lighting/lighting.c \
		  lighting/lighting_utils.c \
		  sphere/hit_sphere.c \
		  sphere/intersect_sphere.c
MRENDER	:= $(addprefix render/, $(MRENDER))

MUTIL	= color.c \
		  color_convert.c \
		  mlx_helper.c \
		  vec3.c \
		  vec3_ops.c \
		  keyhook.c
MUTIL	:= $(addprefix util/, $(MUTIL))

MSRC	+= $(MPARSER) $(MRENDER) $(MUTIL)
MSRC	:= $(addprefix mandatory/src/, $(MSRC))
MOBJ	= $(MSRC:%.c=obj/%.o)

# bonus files
BINC	= -I bonus/inc
BSRC	= main_bonus.c

BPARSER	= parser_bonus.c \
		  parse_elements_bonus.c \
		  parse_objects_bonus.c \
		  parse_objects_utils_bonus.c \
		  parse_utils_bonus.c \
		  parse_validation_bonus.c \
		  parse_options_bonus.c
BPARSER	:= $(addprefix parser/, $(BPARSER))

BRENDER	= render_bonus.c \
		  lighting/lighting_bonus.c \
		  lighting/lighting_utils_bonus.c \
		  find_closest_hit_bonus.c \
		  pattern_bonus.c \
		  texture/texture_bonus.c \
		  texture/texture_uv_bonus.c \
		  bump/bump_bonus.c \
		  bump/bump_normal_bonus.c \
		  bump/bump_uv_bonus.c \
		  bump/bump_preload_bonus.c \
		  cylinder/hit_cylinder_bonus.c \
		  cylinder/intersect_cylinder_bonus.c \
		  plane/hit_plane_bonus.c \
		  plane/intersect_plane_bonus.c \
		  sphere/hit_sphere_bonus.c \
		  sphere/intersect_sphere_bonus.c \
		  cone/hit_cone_bonus.c \
		  cone/intersect_cone_bonus.c
BRENDER	:= $(addprefix render/, $(BRENDER))

BUTIL	= color_bonus.c \
		  color_utils_bonus.c \
		  mlx_helper_bonus.c \
		  vec3_bonus.c \
		  vec3_utils_bonus.c \
		  keyhook_bonus.c
BUTIL	:= $(addprefix util/, $(BUTIL))

BSRC	+= $(BPARSER) $(BRENDER) $(BUTIL)
BSRC	:= $(addprefix bonus/src/, $(BSRC))
BOBJ	= $(BSRC:%.c=obj/%.o)

# compile libs and fdf
all: $(MLX) $(LIBFT) $(NAME)

# compile libs
$(MLX):
	make -C lib/mlx

$(LIBFT):
	make -C lib/libft

# compile from .c to .o inside obj/
obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@ $(MLXINC) $(LIBFTIN) $(MINC) $(BINC)

# compile fdf
$(NAME): $(MOBJ)
	$(CC) $^ -o $@ $(MLXL) $(LIBFTL)

# compile libs and fdf_bonus
bonus: $(MLX) $(LIBFT) $(BNAME)

# compile fdf_bonus
$(BNAME): $(BOBJ)
	$(CC) $^ -o $@ $(MLXL) $(LIBFTL)

clean:
	make -C lib/libft clean
	rm -rf obj

fclean: clean
# 	make -C lib/mlx clean
	make -C lib/libft fclean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all bonus

.PHONY: all clean fclean re bonus
