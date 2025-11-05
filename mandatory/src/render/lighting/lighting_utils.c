/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:54:43 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:31:22 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	diffuse_contribution = color_scale(color_new(255, 255, 255),
			light_intensity);
	diffuse_contribution = color_multiply(diffuse_contribution, object_color);
	return (diffuse_contribution);
}
