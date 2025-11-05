/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:40:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 19:00:07 by joao-alm         ###   ########.fr       */
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
	*u = hit->point.x;
	*v = hit->point.z;
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

static double	get_bump_height(void *img, int x, int y, int wh[2])
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		color;

	if (x < 0)
		x = 0;
	if (x >= wh[0])
		x = wh[0] - 1;
	if (y < 0)
		y = 0;
	if (y >= wh[1])
		y = wh[1] - 1;
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	color = *(int *)(addr + y * line_len + x * (bpp / 8));
	return (((color >> 16) & 0xFF) / 255.0);
}

t_vec3	apply_bump_map(void *mlx, t_hit *hit)
{
	int		wh[2];
	double	uv[2];
	double	height[3];
	int		xy[2];

	(void)mlx;
	if (!hit->object->material.has_bump || !hit->object->material.bump_img)
		return (hit->normal);
	wh[0] = hit->object->material.bump_width;
	wh[1] = hit->object->material.bump_height;
	if (hit->object->type == OBJ_SPHERE)
		get_sphere_uv(hit, &uv[0], &uv[1]);
	else if (hit->object->type == OBJ_PLANE)
		get_plane_uv(hit, &uv[0], &uv[1]);
	else if (hit->object->type == OBJ_CYLINDER)
		get_cylinder_uv(hit, &uv[0], &uv[1]);
	else if (hit->object->type == OBJ_CONE)
		get_cone_uv(hit, &uv[0], &uv[1]);
	else
		return (hit->normal);
	xy[0] = (int)(uv[0] * wh[0]);
	xy[1] = (int)(uv[1] * wh[1]);
	height[0] = get_bump_height(hit->object->material.bump_img, xy[0], xy[1],
			wh);
	height[1] = get_bump_height(hit->object->material.bump_img, xy[0] + 1,
			xy[1], wh);
	height[2] = get_bump_height(hit->object->material.bump_img, xy[0],
			xy[1] + 1, wh);
	return (perturb_normal(hit->normal, height,
			hit->object->material.bump_scale));
}
