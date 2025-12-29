/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:46:54 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:25:15 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_util.h"
#include <stdlib.h>

void	load_textures(t_scene *scene, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < scene->obj_count)
	{
		if (scene->objects[i].texture.enabled)
		{
			printf("%s\n", scene->objects[i].texture.path);
			scene->objects[i].texture.img = mlx_xpm_file_to_image(mlx->ptr,
					scene->objects[i].texture.path,
					&scene->objects[i].texture.width,
					&scene->objects[i].texture.height);
		}
		if (scene->objects[i].bump.enabled)
		{
			printf("%s\n", scene->objects[i].bump.path);
			scene->objects[i].bump.img = mlx_xpm_file_to_image(mlx->ptr,
					scene->objects[i].bump.path, &scene->objects[i].bump.width,
					&scene->objects[i].bump.height);
		}
		i++;
	}
}

void	cleanup_textures(t_scene *scene, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < scene->obj_count)
	{
		if (scene->objects[i].texture.img)
			mlx_destroy_image(mlx->ptr, scene->objects[i].texture.img);
		if (scene->objects[i].texture.path)
			free(scene->objects[i].texture.path);
		if (scene->objects[i].bump.img)
			mlx_destroy_image(mlx->ptr, scene->objects[i].bump.img);
		if (scene->objects[i].bump.path)
			free(scene->objects[i].bump.path);
		i++;
	}
}
