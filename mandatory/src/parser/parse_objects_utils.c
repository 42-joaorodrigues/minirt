/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 21:30:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:16:08 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_int.h"

int	validate_plane(char **params, t_object *obj)
{
	if (!parse_vec3(params[1], &obj->shape.plane.point)
		|| !parse_vec3(params[2], &obj->shape.plane.normal)
		|| !is_valid_normalized(obj->shape.plane.normal)
		|| !parse_color(params[3], &obj->material.color))
		return (0);
	obj->shape.plane.normal = vec3_normalize(obj->shape.plane.normal);
	return (1);
}

int	validate_cylinder(char **params, t_object *obj)
{
	if (!parse_vec3(params[1], &obj->shape.cylinder.center)
		|| !parse_vec3(params[2], &obj->shape.cylinder.axis)
		|| !is_valid_normalized(obj->shape.cylinder.axis)
		|| !ft_stod_valid(params[3], &obj->shape.cylinder.diameter)
		|| !ft_stod_valid(params[4], &obj->shape.cylinder.height)
		|| !parse_color(params[5], &obj->material.color))
		return (0);
	obj->shape.cylinder.axis = vec3_normalize(obj->shape.cylinder.axis);
	return (1);
}
