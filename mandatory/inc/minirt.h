/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:28:29 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:31:22 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx_helper.h"
# include "scene.h"

# define WIDHT 1600
# define HEIGHT 900

typedef struct s_ray
{
	t_vec3		origin; // Camera position
	t_vec3		direction; // Normalized direction vector
}				t_ray;

typedef struct s_hit
{
	int			hit; // Did we hit something?
	double		t; // Distance along ray
	t_vec3		point; // Hit point in world space
	t_vec3		normal; // Surface normal at hit point
	t_object	*object; // Which object was hit
}				t_hit;

typedef struct s_viewport
{
	double		width;
	double		height;
	double		distance;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		lower_left;
}				t_viewport;

typedef struct s_cyl_vars
{
	t_vec3		oc;
	t_vec3		d_proj;
	t_vec3		oc_proj;
	double		abc[3];
	double		disc;
	double		t_vals[2];
}				t_cyl_vars;

/* Parser */
void			parse_scene(char *filepath, t_scene *scene);

/* Keyhook */
void			keyhook(t_mlx *mlx);

/* Render */
void			render_scene(t_scene *scene, t_mlx *mlx);
t_color			calculate_lighting(t_scene *scene, t_hit *hit, t_vec3 cam_pos,
					void *mlx);
t_color			calculate_ambient(t_ambient *ambient, t_color object_color);
t_color			calculate_diffuse(t_light *light, t_vec3 hit_point,
					t_vec3 normal, t_color object_color);
t_hit			find_closest_hit(t_ray *ray, t_scene *scene);

/* Sphere */
int				intersect_sphere(t_ray *ray, t_sphere *sphere, double *t);
void			process_sphere_hit(t_ray *ray, t_object *obj, double t,
					t_hit *closest);

/* Plane */
int				intersect_plane(t_ray *ray, t_plane *plane, double *t);
void			process_plane_hit(t_ray *ray, t_object *obj, double t,
					t_hit *closest);

/* Cylinder */
int				intersect_cylinder(t_ray *ray, t_cylinder *cyl, double *t);
void			process_cylinder_hit(t_ray *ray, t_object *obj, double t,
					t_hit *closest);

#endif