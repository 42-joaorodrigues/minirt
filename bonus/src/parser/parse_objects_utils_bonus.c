/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:45:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:51:45 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_int_bonus.h"
#include <stddef.h>

void	init_material(t_material *mat, t_color color)
{
	mat->color = color;
	mat->specular = 0.5;
	mat->shininess = 32.0;
	mat->pattern = PATTERN_NONE;
	mat->pat_scale = 1.0;
	mat->pat_type = 1;
	mat->bump_path = NULL;
	mat->bump_scale = 1.0;
	mat->has_bump = 0;
	mat->bump_img = NULL;
	mat->bump_width = 0;
	mat->bump_height = 0;
	mat->texture_path = NULL;
	mat->has_texture = 0;
	mat->texture_img = NULL;
	mat->texture_width = 0;
	mat->texture_height = 0;
}

int	validate_sphere_params(char **params, t_object *obj)
{
	if (!parse_vec3(params[1], &obj->shape.sphere.center)
		|| !ft_stod_valid(params[2], &obj->shape.sphere.diameter)
		|| !parse_color(params[3], &obj->material.color))
		return (0);
	return (1);
}

int	validate_plane_params(char **params, t_object *obj)
{
	if (!parse_vec3(params[1], &obj->shape.plane.point)
		|| !parse_vec3(params[2], &obj->shape.plane.normal)
		|| !is_valid_normalized(obj->shape.plane.normal)
		|| !parse_color(params[3], &obj->material.color))
		return (0);
	return (1);
}

int	validate_cylinder_params(char **params, t_object *obj)
{
	if (!parse_vec3(params[1], &obj->shape.cylinder.center)
		|| !parse_vec3(params[2], &obj->shape.cylinder.axis)
		|| !is_valid_normalized(obj->shape.cylinder.axis)
		|| !ft_stod_valid(params[3], &obj->shape.cylinder.diameter)
		|| !ft_stod_valid(params[4], &obj->shape.cylinder.height)
		|| !parse_color(params[5], &obj->material.color))
		return (0);
	return (1);
}

int	find_color_index(char **params)
{
	int	color_idx;

	color_idx = 5;
	while (params[color_idx] && !ft_strchr(params[color_idx], ','))
		color_idx++;
	return (color_idx);
}
