/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:25:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 22:06:58 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_int.h"

int	parse_vec3(char *str, t_vec3 *vec)
{
	char	**coords;
	int		result;

	coords = ft_split(str, ",");
	if (!coords || !coords[0] || !coords[1] || !coords[2] || coords[3])
	{
		free_split(coords);
		return (0);
	}
	result = 1;
	if (!ft_stod_valid(coords[0], &vec->x) || !ft_stod_valid(coords[1], &vec->y)
		|| !ft_stod_valid(coords[2], &vec->z))
		result = 0;
	free_split(coords);
	return (result);
}

static int	validate_rgb_values(char **rgb, int *rgb_vals)
{
	if (!ft_atoi_valid(rgb[0], &rgb_vals[0])
		|| !ft_atoi_valid(rgb[1], &rgb_vals[1])
		|| !ft_atoi_valid(rgb[2], &rgb_vals[2]))
		return (0);
	return (1);
}

int	parse_color(char *str, t_color *color)
{
	char	**rgb;
	char	*semicolon;
	int		rgb_vals[3];

	semicolon = ft_strchr(str, ';');
	if (semicolon)
		*semicolon = '\0';
	rgb = ft_split(str, ",");
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_split(rgb);
		return (0);
	}
	if (!validate_rgb_values(rgb, rgb_vals))
	{
		free_split(rgb);
		return (0);
	}
	color->r = rgb_vals[0];
	color->g = rgb_vals[1];
	color->b = rgb_vals[2];
	free_split(rgb);
	return (is_valid_color(*color));
}

char	*skip_spaces(char *s)
{
	while (*s && (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r'))
		s++;
	return (s);
}
