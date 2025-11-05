/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:20:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:31:44 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_int.h"

static void	init_material(t_material *mat, t_color color)
{
	mat->color = color;
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
	if (!validate_plane(params, obj))
	{
		free_split(params);
		return (ft_puterr("Invalid Plane param"));
	}
	init_material(&obj->material, obj->material.color);
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
	if (!validate_cylinder(params, obj))
	{
		free_split(params);
		return (ft_puterr("Invalid Cylinder param"));
	}
	init_material(&obj->material, obj->material.color);
	scene->obj_count++;
	free_split(params);
	return (0);
}
