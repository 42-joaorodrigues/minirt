/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:48:28 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/04 14:23:56 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "mlx_helper_bonus.h"



void	render_scene(t_scene *scene, t_mlx *mlx)
{
	t_viewport	vp;
	int 		x;
	int 		y;

	(void)scene;
	(void)vp;
	ft_init_mlx_img_fullscreen(mlx);
	y = -1;
	while (++y < mlx->win_height)
	{
		x = -1;
		while (++x < mlx->win_width)
			; // do domething
	}
	ft_mlx_put_img_clean(mlx);

	int offset_x = mlx->win_width / 2 - 50;
	int offset_y = mlx->win_height / 2;
	mlx_string_put(mlx->ptr, mlx->win, offset_x, offset_y, 0xFFFFFF,
		"miniRT in progress...");
}
