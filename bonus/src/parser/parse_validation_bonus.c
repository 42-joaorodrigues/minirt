/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:30:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/03 18:30:26 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int_bonus.h"
#include <math.h>

int	is_valid_normalized(t_vec3 vec)
{
	double	magnitude;
	double	tolerance;

	tolerance = 0.01;
	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (fabs(magnitude - 1.0) > tolerance)
		return (0);
	if (vec.x < -1.0 || vec.x > 1.0
		|| vec.y < -1.0 || vec.y > 1.0
		|| vec.z < -1.0 || vec.z > 1.0)
		return (0);
	return (1);
}

int	is_valid_color(t_color color)
{
	if (color.r < 0 || color.r > 255
		|| color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		return (0);
	return (1);
}

int	is_valid_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}
