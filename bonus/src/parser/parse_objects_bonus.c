/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:20:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 21:04:34 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int_bonus.h"
#include "libft.h"

static void	init_material(t_material *mat, t_color color)
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

int	parse_sphere(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (scene->obj_count >= MAX_OBJECTS)
		return (ft_puterr("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 4)
	{
		free_split(params);
		return (ft_puterr("Invalid Sphere param count"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_SPHERE;
	if (!parse_vec3(params[1], &obj->shape.sphere.center)
		|| !ft_stod_valid(params[2], &obj->shape.sphere.diameter)
		|| !parse_color(params[3], &obj->material.color))
	{
		free_split(params);
		return (ft_puterr("Invalid Sphere params"));
	}
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, 4, &obj->material);
	scene->obj_count++;
	free_split(params);
	return (0);
}

int	parse_plane(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (scene->obj_count >= MAX_OBJECTS)
		return (ft_puterr("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 4)
	{
		free_split(params);
		return (ft_puterr("Invalid Plane params count"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_PLANE;
	if (!parse_vec3(params[1], &obj->shape.plane.point)
		|| !parse_vec3(params[2], &obj->shape.plane.normal)
		|| !is_valid_normalized(obj->shape.plane.normal)
		|| !parse_color(params[3], &obj->material.color))
	{
		free_split(params);
		return (ft_puterr("Invalid Plane param"));
	}
	obj->shape.plane.normal = vec3_normalize(obj->shape.plane.normal);
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, 4, &obj->material);
	scene->obj_count++;
	free_split(params);
	return (0);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (scene->obj_count >= MAX_OBJECTS)
		return (ft_puterr("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 6)
	{
		free_split(params);
		return (ft_puterr("Invalid Cylinder param count"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_CYLINDER;
	if (!parse_vec3(params[1], &obj->shape.cylinder.center)
		|| !parse_vec3(params[2], &obj->shape.cylinder.axis)
		|| !is_valid_normalized(obj->shape.cylinder.axis)
		|| !ft_stod_valid(params[3], &obj->shape.cylinder.diameter)
		|| !ft_stod_valid(params[4], &obj->shape.cylinder.height)
		|| !parse_color(params[5], &obj->material.color))
	{
		free_split(params);
		return (ft_puterr("Invalid Cylinder param"));
	}
	obj->shape.cylinder.axis = vec3_normalize(obj->shape.cylinder.axis);
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, 6, &obj->material);
	scene->obj_count++;
	free_split(params);
	return (0);
}

int	parse_cone(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;
	int			color_idx;

	if (scene->obj_count >= MAX_OBJECTS)
		return (ft_puterr("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 6)
	{
		free_split(params);
		return (ft_puterr("Invalid Cone param count"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_CONE;
	color_idx = 5;
	while (params[color_idx] && !ft_strchr(params[color_idx], ','))
		color_idx++;
	if (!parse_vec3(params[1], &obj->shape.cone.center)
		|| !parse_vec3(params[2], &obj->shape.cone.axis)
		|| !is_valid_normalized(obj->shape.cone.axis)
		|| !ft_stod_valid(params[3], &obj->shape.cone.diameter)
		|| !ft_stod_valid(params[4], &obj->shape.cone.height)
		|| !parse_color(params[color_idx], &obj->material.color))
	{
		free_split(params);
		return (ft_puterr("Invalid Cone param"));
	}
	obj->shape.cone.axis = vec3_normalize(obj->shape.cone.axis);
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, color_idx + 1, &obj->material);
	scene->obj_count++;
	free_split(params);
	return (0);
}
