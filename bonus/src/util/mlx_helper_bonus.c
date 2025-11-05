/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:55:23 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/04 14:16:11 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_helper_bonus.h"
#include <stdlib.h>

void	ft_init_mlx(t_mlx *mlx, int width, int height, char *title)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, width, height, title);
	mlx->win_width = width;
	mlx->win_height = height;
}

void	ft_init_mlx_img_fullscreen(t_mlx *mlx)
{
	mlx->img.ptr = mlx_new_image(mlx->ptr, mlx->win_width, mlx->win_height);
	mlx->img.height = mlx->win_height;
	mlx->img.width = mlx->win_width;
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
}

void	set_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_mlx_put_img_clean(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
}

void	ft_cleanup_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
}