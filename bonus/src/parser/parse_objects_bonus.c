/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:20:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:59:32 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_int_bonus.h"

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
	if (!validate_sphere_params(params, obj))
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
	if (!validate_plane_params(params, obj))
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
	if (!validate_cylinder_params(params, obj))
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

static int	validate_cone_params(char **params, t_object *obj, int color_idx)
{
	if (!parse_vec3(params[1], &obj->shape.cone.center)
		|| !parse_vec3(params[2], &obj->shape.cone.axis)
		|| !is_valid_normalized(obj->shape.cone.axis)
		|| !ft_stod_valid(params[3], &obj->shape.cone.diameter)
		|| !ft_stod_valid(params[4], &obj->shape.cone.height)
		|| !parse_color(params[color_idx], &obj->material.color))
		return (0);
	return (1);
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
	color_idx = find_color_index(params);
	if (!validate_cone_params(params, obj, color_idx))
	{
		free_split(params);
		return (ft_puterr("Invalid Cone param"));
	}
	obj->shape.cone.axis = vec3_normalize(obj->shape.cone.axis);
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, color_idx + 1, &obj->material);
	scene->obj_count++;
	return (free_split(params), 0);
}
