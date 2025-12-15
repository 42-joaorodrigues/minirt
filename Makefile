# So Long
# by joao-alm

NAME   		= miniRT
CC     		= cc
CFLAGS 		= -Wall -Werror -Wextra -Ofast -march=native -Wno-incompatible-pointer-types
O_DIR		= obj
HEADER		= $(O_DIR)/.header

all: $(NAME)

SRC				= src/game/enemy_bonus.c \
				  src/game/enemy_collision_bonus.c \
				  src/game/enemy_move_horizontal_bonus.c \
				  src/game/enemy_move_vertical_bonus.c \
				  src/game/map_exit_animation_bonus.c \
				  src/game/player.c \
				  src/input/keyhooks.c \
				  src/parser/flood_fill.c \
				  src/parser/parse_elements.c \
				  src/parser/parse_enemy_bonus.c \
				  src/parser/parse_map.c \
				  src/parser/sprite_ids.c \
				  src/parser/void_walls.c \
				  src/render/render.c \
				  src/render/render_counter_bonus.c \
				  src/render/render_enemy_bonus.c \
				  src/render/render_player.c \
				  src/render/sprites.c \
				  src/util/exit.c \
				  src/util/mlx_util.c \
				  src/util/util.c \
				  src/main.c
OBJ 			= $(SRC:%.c=$(O_DIR)/%.o)

libft:
	@git clone https://github.com/42-joaorodrigues/mylib.git libft > /dev/null 2>&1
	@echo "Libft downloaded successfully"

mlx:
	@git clone https://github.com/42-joaorodrigues/compiled_mlx.git mlx > /dev/null 2>&1
	@echo "Mlx downloaded successfully"

$(O_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinc -Imlx -Ilibft/inc

$(NAME): $(HEADER) libft mlx $(OBJ)
	@make -C libft --no-print-directory > /dev/null 2>&1
	@echo "Libft compiled successfully"
#	@make -C mlx --no-print-directory > /dev/null 2>&1
#	@echo "Mlx compiled successfully"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -Llibft -lft -Lmlx -lmlx -lXext -lX11
	@echo "So_Long compiled successfully"

bonus: $(NAME)

clean:
	@rm -rf $(O_DIR)
	@echo "So_Long objects removed successfully"

fclean: libft mlx
	@rm -rf $(O_DIR)
	@rm -rf $(NAME)
	@echo "So Long objects & executable removed successfully"
	@make -C libft fclean --no-print-directory > /dev/null 2>&1
	@echo "Libft objects & executable removed successfully"
#	@make -C mlx clean --no-print-directory > /dev/null 2>&1
#	@echo "Mlx objects & executable removed successfully"

re: fclean all

$(HEADER):
	@mkdir -p $(dir $@)
	@touch $@
	@printf "\n"
	@printf "█████████████████████████████\n"
	@printf "        ██  █▓███  ██  █▓███ \n"
	@printf "joao-alm  █████      █████   \n"
	@printf "╔═╗┌─┐  ╦  ┌─┐┌┐┌┌─┐\n"
	@printf "╚═╗│ │  ║  │ │││││ ┬\n"
	@printf "╚═╝└─┘  ╩═╝└─┘┘└┘└─┘\n\n"

.PHONY: all bonus clean fclean re
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
