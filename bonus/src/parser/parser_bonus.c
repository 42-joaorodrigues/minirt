/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:01:22 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/03 18:30:44 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int_bonus.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void	init_scene(t_scene *scene)
{
	scene->ambient.set = 0;
	scene->camera.set = 0;
	scene->light_count = 0;
	scene->obj_count = 0;
}

static int	parse_line(char *line, t_scene *scene)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!trimmed || !*trimmed || *trimmed == '#')
		return (0);
	if (trimmed[0] == 'A' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (parse_ambient(trimmed, scene));
	if (trimmed[0] == 'C' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (parse_camera(trimmed, scene));
	if (trimmed[0] == 'L' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (parse_light(trimmed, scene));
	if (trimmed[0] == 's' && trimmed[1] == 'p' && (trimmed[2] == ' '
			|| trimmed[2] == '\t'))
		return (parse_sphere(trimmed, scene));
	if (trimmed[0] == 'p' && trimmed[1] == 'l' && (trimmed[2] == ' '
			|| trimmed[2] == '\t'))
		return (parse_plane(trimmed, scene));
	if (trimmed[0] == 'c' && trimmed[1] == 'y' && (trimmed[2] == ' '
			|| trimmed[2] == '\t'))
		return (parse_cylinder(trimmed, scene));
	if (trimmed[0] == 'c' && trimmed[1] == 'o' && (trimmed[2] == ' '
			|| trimmed[2] == '\t'))
		return (parse_cone(trimmed, scene));
	return (ft_puterr("Invalid scene configuration"));
}

static char	**read_file(char *filepath)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		ft_puterr_exit("Failed to open scene file");
	lines = malloc(sizeof(char *) * 1000);
	if (!lines)
		ft_puterr_exit("Memory allocation failed");
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines[count++] = line;
		line = get_next_line(fd);
	}
	lines[count] = NULL;
	close(fd);
	return (lines);
}

static void	validate_scene(t_scene *scene)
{
	if (!scene->ambient.set)
		ft_puterr_exit("Missing ambient lighting definition");
	if (!scene->camera.set)
		ft_puterr_exit("Missing camera definition");
	if (scene->light_count == 0)
		ft_puterr_exit("At least one light is required");
}

void	parse_scene(char *filepath, t_scene *scene)
{
	char	**lines;
	int		i;

	init_scene(scene);
	lines = read_file(filepath);
	i = 0;
	while (lines[i])
	{
		if (parse_line(lines[i], scene) != 0)
		{
			free_split(lines);
			exit(1);
		}
		i++;
	}
	free_split(lines);
	validate_scene(scene);
}