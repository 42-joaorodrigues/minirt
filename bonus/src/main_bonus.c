/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:00:45 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/03 20:20:15 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt_bonus.h"
#include "mlx.h"
#include "mlx_helper_bonus.h"
#include <stddef.h>

void	handle_args(int ac, char **av)
{
	size_t	file_len;

	if (ac != 2)
		ft_puterr_exit("Usage: ./miniRT_bonus scene_file.rt");
	file_len = ft_strlen(av[1]);
	if (file_len < 3 || ft_strcmp(av[1] + file_len - 3, ".rt") != 0)
		ft_puterr_exit("Scene file must be of type .rt");
}

int	main(int ac, char **av)
{
	t_data dt;
	t_mlx *mlx;

	handle_args(ac, av);
	parse_scene(av[1], &dt.scene);
	ft_putstr("Scene parsed successfully!\n");
	mlx = &dt.mlx;
	ft_init_mlx(mlx, WIDHT, HEIGHT, "miniRT");
	mlx_string_put(mlx->ptr, mlx->win, mlx->win_width / 2, mlx->win_height / 2,
		0xFFFFFF, "miniRT in progress...");
	mlx_loop(mlx->ptr);
	ft_cleanup_mlx(mlx);
	return (0);
}