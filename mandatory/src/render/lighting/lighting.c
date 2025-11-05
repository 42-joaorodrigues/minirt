/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:54:43 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:59:56 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stddef.h>

int	is_in_shadow(t_scene *scene, t_vec3 hit_point, t_light *light)
{
	t_ray	shadow_ray;
	t_vec3	to_light;
	double	light_distance;
	t_hit	shadow_hit;

	to_light = vec3_sub(light->pos, hit_point);
	light_distance = sqrt(vec3_dot(to_light, to_light));
	shadow_ray.origin = vec3_add(hit_point, vec3_scale(to_light, 0.001
				/ light_distance));
	shadow_ray.direction = vec3_normalize(to_light);
	shadow_hit = find_closest_hit(&shadow_ray, scene);
	if (shadow_hit.hit && shadow_hit.t < light_distance - 0.001)
		return (1);
	return (0);
}

t_color	calculate_lighting(t_scene *scene, t_hit *hit, t_vec3 cam_pos,
		void *mlx)
{
	t_color	final_color;
	t_color	diffuse;

	(void)cam_pos;
	(void)mlx;
	final_color = calculate_ambient(&scene->ambient,
			hit->object->material.color);
	if (!is_in_shadow(scene, hit->point, &scene->light))
	{
		diffuse = calculate_diffuse(&scene->light, hit->point, hit->normal,
				hit->object->material.color);
		final_color = color_add(final_color, diffuse);
	}
	final_color = color_clamp(final_color);
	return (final_color);
}
