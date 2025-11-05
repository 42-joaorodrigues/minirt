/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:30:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 19:05:24 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "mlx.h"
#include <math.h>

static void	get_sphere_uv(t_hit *hit, double *u, double *v)
{
	t_vec3	local;
	double	theta;
	double	phi;

	local = vec3_sub(hit->point, hit->object->shape.sphere.center);
	local = vec3_normalize(local);
	theta = atan2(local.z, local.x);
	phi = acos(local.y);
	*u = theta / (2.0 * M_PI);
	*v = phi / M_PI;
	if (*u < 0)
		*u += 1.0;
}

static void	get_plane_uv(t_hit *hit, double *u, double *v)
{
	*u = hit->point.x * 0.1;
	*v = hit->point.z * 0.1;
	*u = *u - floor(*u);
	*v = *v - floor(*v);
}

static void	get_cylinder_uv(t_hit *hit, double *u, double *v)
{
	t_vec3	local;
	t_vec3	axis;
	double	theta;
	double	projection;

	axis = hit->object->shape.cylinder.axis;
	local = vec3_sub(hit->point, hit->object->shape.cylinder.center);
	projection = vec3_dot(local, axis);
	*v = (projection / hit->object->shape.cylinder.height) + 0.5;
	local = vec3_sub(local, vec3_scale(axis, projection));
	local = vec3_normalize(local);
	theta = atan2(local.z, local.x);
	*u = theta / (2.0 * M_PI);
	if (*u < 0)
		*u += 1.0;
}

static void	get_cone_uv(t_hit *hit, double *u, double *v)
{
	t_vec3	local;
	t_vec3	axis;
	double	theta;
	double	projection;

	axis = hit->object->shape.cone.axis;
	local = vec3_sub(hit->point, hit->object->shape.cone.center);
	projection = vec3_dot(local, axis);
	*v = (projection / hit->object->shape.cone.height) + 0.5;
	local = vec3_sub(local, vec3_scale(axis, projection));
	local = vec3_normalize(local);
	theta = atan2(local.z, local.x);
	*u = theta / (2.0 * M_PI);
	if (*u < 0)
		*u += 1.0;
}

static t_color	sample_texture_at(void *img, int x, int y, int wh[2])
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		pixel;
	t_color	color;

	if (x < 0)
		x = 0;
	if (x >= wh[0])
		x = wh[0] - 1;
	if (y < 0)
		y = 0;
	if (y >= wh[1])
		y = wh[1] - 1;
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	pixel = *(int *)(addr + y * line_len + x * (bpp / 8));
	color.r = (pixel >> 16) & 0xFF;
	color.g = (pixel >> 8) & 0xFF;
	color.b = pixel & 0xFF;
	return (color);
}

t_color	get_texture_color(t_hit *hit)
{
	double	uv[2];
	int		xy[2];
	int		wh[2];

	if (!hit->object->material.has_texture
		|| !hit->object->material.texture_img)
		return (hit->object->material.color);
	wh[0] = hit->object->material.texture_width;
	wh[1] = hit->object->material.texture_height;
	if (hit->object->type == OBJ_SPHERE)
		get_sphere_uv(hit, &uv[0], &uv[1]);
	else if (hit->object->type == OBJ_PLANE)
		get_plane_uv(hit, &uv[0], &uv[1]);
	else if (hit->object->type == OBJ_CYLINDER)
		get_cylinder_uv(hit, &uv[0], &uv[1]);
	else if (hit->object->type == OBJ_CONE)
		get_cone_uv(hit, &uv[0], &uv[1]);
	else
		return (hit->object->material.color);
	xy[0] = (int)(uv[0] * wh[0]);
	xy[1] = (int)(uv[1] * wh[1]);
	return (sample_texture_at(hit->object->material.texture_img, xy[0], xy[1],
			wh));
}
