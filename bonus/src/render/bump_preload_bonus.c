/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_preload_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:10:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 19:05:23 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"
#include "mlx.h"
#include <stddef.h>

void	preload_bump_textures(t_scene *scene, void *mlx)
{
	int	i;

	i = 0;
	while (i < scene->obj_count)
	{
		if (scene->objects[i].material.has_bump
			&& scene->objects[i].material.bump_path
			&& !scene->objects[i].material.bump_img)
		{
			scene->objects[i].material.bump_img = mlx_xpm_file_to_image(mlx,
					scene->objects[i].material.bump_path,
					&scene->objects[i].material.bump_width,
					&scene->objects[i].material.bump_height);
		}
		if (scene->objects[i].material.has_texture
			&& scene->objects[i].material.texture_path
			&& !scene->objects[i].material.texture_img)
		{
			scene->objects[i].material.texture_img = mlx_xpm_file_to_image(mlx,
					scene->objects[i].material.texture_path,
					&scene->objects[i].material.texture_width,
					&scene->objects[i].material.texture_height);
		}
		i++;
	}
}

void	cleanup_bump_textures(t_scene *scene, void *mlx)
{
	int	i;

	i = 0;
	while (i < scene->obj_count)
	{
		if (scene->objects[i].material.bump_img)
		{
			mlx_destroy_image(mlx, scene->objects[i].material.bump_img);
			scene->objects[i].material.bump_img = NULL;
		}
		if (scene->objects[i].material.texture_img)
		{
			mlx_destroy_image(mlx, scene->objects[i].material.texture_img);
			scene->objects[i].material.texture_img = NULL;
		}
		i++;
	}
}
