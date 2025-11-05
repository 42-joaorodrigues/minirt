/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:01:31 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:17:09 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H

# include "scene.h"

/* Parse elements */
int		parse_ambient(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);

/* Parse objects */
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);

/* Parse objects utils */
int		validate_plane(char **params, t_object *obj);
int		validate_cylinder(char **params, t_object *obj);

/* Parse utils */
int		parse_vec3(char *str, t_vec3 *vec);
int		parse_color(char *str, t_color *color);
char	*skip_spaces(char *s);

/* Parse validation */
int		is_valid_normalized(t_vec3 vec);
int		is_valid_color(t_color color);
int		is_valid_range(double value, double min, double max);

#endif