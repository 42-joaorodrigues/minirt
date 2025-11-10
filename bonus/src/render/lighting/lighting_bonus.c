/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:54:43 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/10 16:08:33 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>
#include <stddef.h>

/*
** Casts a shadow ray from hit point toward light.
** Returns 1 if an object blocks the light path.
*/
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

t_color	calculate_ambient(t_ambient *ambient, t_color object_color)
{
	t_color	ambient_contribution;

	ambient_contribution = color_multiply(ambient->color, object_color);
	ambient_contribution = color_scale(ambient_contribution, ambient->ratio);
	return (ambient_contribution);
}

t_color	calculate_lighting(t_scene *scene, t_hit *hit, t_vec3 cam_pos,
		void *mlx)
{
	t_color			final_color;
	t_color			object_color;
	t_vec3			bumped_normal;
	t_light_calc	calc;
	int				i;

	object_color = get_pattern_color(hit);
	bumped_normal = hit->normal;
	if (hit->object->material.has_bump && hit->object->material.bump_img)
		bumped_normal = apply_bump_map(mlx, hit);
	calc = (t_light_calc){hit->point, bumped_normal, cam_pos, object_color,
		&hit->object->material};
	final_color = calculate_ambient(&scene->ambient, object_color);
	i = -1;
	while (++i < scene->light_count)
	{
		if (!is_in_shadow(scene, hit->point, &scene->lights[i]))
		{
			final_color = color_add(final_color,
					calc_diff(&scene->lights[i], &calc));
			final_color = color_add(final_color,
					calc_spec(&scene->lights[i], &calc));
		}
	}
	return (color_clamp(final_color));
}
