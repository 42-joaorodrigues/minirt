/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:00:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 19:05:23 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene_bonus.h"

static char	*dup_str(const char *s)
{
	char    *res;
	size_t  len;
	size_t  i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

static int	parse_pattern_option(char *value, t_material *mat)
{
	char	**parts;
	int		result;

	parts = ft_split(value, ",");
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		free_split(parts);
		return (0);
	}
	result = 1;
	if (!ft_stod_valid(parts[0], &mat->pat_scale)
		|| !ft_atoi_valid(parts[1], &mat->pat_type))
		result = 0;
	else
		mat->pattern = PATTERN_CHECKER;
	free_split(parts);
	return (result);
}

static int	parse_bump_option(char *value, t_material *mat)
{
	char    **parts;
	int     result;

	parts = ft_split(value, ",");
	if (!parts || !parts[0])
	{
		free_split(parts);
		return (0);
	}
	result = 1;
	mat->bump_path = dup_str(parts[0]);
	mat->bump_scale = 1.0;
	mat->has_bump = 1;
	if (parts[1])
	{
		if (!ft_stod_valid(parts[1], &mat->bump_scale))
			result = 0;
	}
	free_split(parts);
	return (result);
}

static int	parse_texture_option(char *value, t_material *mat)
{
	mat->texture_path = dup_str(value);
	mat->has_texture = 1;
	return (1);
}

void	parse_material_options(char **params, int start_idx, t_material *mat)
{
	int		i;
	char	*colon;

	i = start_idx;
	while (params[i])
	{
		colon = ft_strchr(params[i], ':');
		if (colon)
		{
			*colon = '\0';
			if (ft_strcmp(params[i], "pat") == 0)
				parse_pattern_option(colon + 1, mat);
			else if (ft_strcmp(params[i], "bum") == 0)
				parse_bump_option(colon + 1, mat);
			else if (ft_strcmp(params[i], "txm") == 0)
				parse_texture_option(colon + 1, mat);
		}
		i++;
	}
}
