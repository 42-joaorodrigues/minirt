/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:41:24 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 13:43:49 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3_bonus.h"
#include <math.h>

t_vec3  vec3_new(double x, double y, double z)
{
    t_vec3  v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

t_vec3  vec3_add(t_vec3 a, t_vec3 b)
{
    t_vec3  result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return (result);
}

t_vec3  vec3_sub(t_vec3 a, t_vec3 b)
{
    t_vec3  result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return (result);
}

t_vec3  vec3_scale(t_vec3 v, double scalar)
{
    t_vec3  result;

    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return (result);
}

t_vec3  vec3_negate(t_vec3 v)
{
    t_vec3  result;

    result.x = -v.x;
    result.y = -v.y;
    result.z = -v.z;
    return (result);
}

double  vec3_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3  vec3_cross(t_vec3 a, t_vec3 b)
{
    t_vec3  result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return (result);
}

double  vec3_magnitude(t_vec3 v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3  vec3_normalize(t_vec3 v)
{
    double  mag;

    mag = vec3_magnitude(v);
    if (mag == 0.0)
        return (vec3_new(0, 0, 0));
    return (vec3_new(v.x / mag, v.y / mag, v.z / mag));
}