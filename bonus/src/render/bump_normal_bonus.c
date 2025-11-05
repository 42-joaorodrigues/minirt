/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_normal_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:42:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 18:25:09 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3_bonus.h"
#include <math.h>

static t_vec3	compute_tangent(t_vec3 normal)
{
	t_vec3	tangent;

	if (fabs(normal.y) < 0.999)
		tangent = vec3_normalize(vec3_cross(normal, vec3_new(0, 1, 0)));
	else
		tangent = vec3_normalize(vec3_cross(normal, vec3_new(1, 0, 0)));
	return (tangent);
}

t_vec3	perturb_normal(t_vec3 normal, double height[3], double scale)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	perturb;
	t_vec3	new_normal;
	double	dx;
	double	dy;

	dx = (height[1] - height[0]) * scale;
	dy = (height[2] - height[0]) * scale;
	tangent = compute_tangent(normal);
	bitangent = vec3_cross(normal, tangent);
	perturb = vec3_add(vec3_scale(tangent, -dx), vec3_scale(bitangent, -dy));
	new_normal = vec3_add(normal, perturb);
	new_normal = vec3_normalize(new_normal);
	return (new_normal);
}
