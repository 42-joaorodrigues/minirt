/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:28:29 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/03 20:12:26 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
#define MINIRT_BONUS_H

#include "mlx_helper_bonus.h"
#include "scene_bonus.h"

# define WIDHT 1600
# define HEIGHT 900

typedef struct s_data
{
	t_scene	scene;
	t_mlx	mlx;
}	t_data;

/* Parser */
void	parse_scene(char *filepath, t_scene *scene);

#endif