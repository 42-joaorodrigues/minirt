/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:17:56 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:25:19 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_util.h"
#include <stdlib.h>

static int	ft_exit(t_keyhook *kh)
{
	ft_cleanup_mlx(kh->scene, kh->mlx);
	exit(0);
	return (0);
}

static int	handle_keypress(int key, t_keyhook *kh)
{
	if (key == ESC_KEY)
		ft_exit(kh);
	return (0);
}

void	keyhook(t_scene *scene, t_mlx *mlx)
{
	static t_keyhook	kh;

	kh.mlx = mlx;
	kh.scene = scene;
	mlx_hook(mlx->win, 2, 1L << 0, handle_keypress, &kh);
	mlx_hook(mlx->win, 17, 1L << 0, ft_exit, &kh);
}
