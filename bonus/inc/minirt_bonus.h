/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:28:29 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/04 14:16:50 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "mlx_helper_bonus.h"
# include "scene_bonus.h"

# define WIDHT 1600
# define HEIGHT 900

typedef struct s_viewport
{
	double		width; // Viewport width in world units
	double		height; // Viewport height in world units
	double		distance; // Distance from camera (typically 1.0)
	t_vec3		horizontal; // Horizontal vector across viewport
	t_vec3		vertical; // Vertical vector across viewport
	t_vec3		lower_left; // Lower left corner position
}				t_viewport;

/* Parser */
void			parse_scene(char *filepath, t_scene *scene);

/* Keyhook */
void			keyhook(t_mlx *mlx);

/* Render */
void			render_scene(t_scene *scene, t_mlx *mlx);

#endif