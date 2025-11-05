/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:17:56 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:04:58 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_helper.h"
#include <stdlib.h>

int	ft_exit(t_mlx *mlx)
{
	ft_cleanup_mlx(mlx);
	exit(0);
	return (0);
}

int	handle_keypress(int key, t_mlx *mlx)
{
	if (key == ESC_KEY)
		ft_exit(mlx);
	return (0);
}

void	keyhook(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L << 0, handle_keypress, mlx);
	mlx_hook(mlx->win, 17, 1L << 0, ft_exit, mlx);
}
