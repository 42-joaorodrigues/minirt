/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:54:43 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 14:58:21 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_color	calculate_ambient(t_ambient *ambient, t_color object_color)
{
	t_color	ambient_contribution;

	ambient_contribution = color_multiply(ambient->color, object_color);
	ambient_contribution = color_scale(ambient_contribution, ambient->ratio);
	return (ambient_contribution);
}

t_color	calculate_diffuse(t_light *light, t_vec3 hit_point, t_vec3 normal,
		t_color object_color)
{
	t_vec3	light_dir;
	double	light_intensity;
	t_color	diffuse_contribution;

	light_dir = vec3_sub(light->pos, hit_point);
	light_dir = vec3_normalize(light_dir);
	light_intensity = vec3_dot(normal, light_dir);
	if (light_intensity < 0)
		light_intensity = 0;
	light_intensity *= light->brightness;
	diffuse_contribution = color_multiply(light->color, object_color);
	diffuse_contribution = color_scale(diffuse_contribution, light_intensity);
	return (diffuse_contribution);
}

t_color	calculate_lighting(t_scene *scene, t_hit *hit)
{
	t_color	final_color;
	t_color	ambient;
	t_color	diffuse;
	int		i;

	ambient = calculate_ambient(&scene->ambient, hit->object->material.color);
	final_color = ambient;
	i = 0;
	while (i < scene->light_count)
	{
		diffuse = calculate_diffuse(&scene->lights[i], hit->point, hit->normal,
				hit->object->material.color);
		final_color = color_add(final_color, diffuse);
		i++;
	}
	final_color = color_clamp(final_color);
	return (final_color);
}
