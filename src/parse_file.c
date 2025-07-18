/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:45:37 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/16 10:58:57 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_line(char *line, t_data *data)
{
	if (is_texture_line(line))
	{
		printf("Texture trouvée: %s", line);
		if (!parse_texture_line(line, &data->config))
			return (0);
		return (1);
	}
	else if (is_color_line(line))
	{
		printf("Couleur trouvée: %s", line);
		if (!parse_color_line_safe(line, &data->config))
			return (0);
		return (1);
	}
	else if (is_map_line(line))
	{
		printf("Ligne de carte trouvée: %s", line);
		add_map_line(data, line);
		return (1);
	}
	else
	{
		printf("Ligne ignorée : %s", line);
		return (1);
	}
}

int	parse_file(const char *filename, t_data *data)
{
	int		fd;
	int		line_number;
	char	*line;

	line_number = 1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: ouverture fichier\n");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		if (line[0] != '\n' && line[0] != '\0')
		{
			printf("Ligne %d:\n", line_number);
			if (!process_line(line, data))
			{
				free(line);
				close(fd);
				return (1);
			}
		}
		line_number++;
		free(line);
	}
	close(fd);
	return (0);
}

int	is_texture_line(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

int	is_color_line(char *line)
{
	if (!line)
		return (0);
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_chars;

	if (!line)
		return (0);
	i = 0;
	has_map_chars = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			has_map_chars = 1;
		}
		i++;
	}
	return (has_map_chars);
}

static int	get_rgb_value(char *rgb_str)
{
	char	*temp;
	int		value;

	temp = ft_strtrim(rgb_str, " \t\n");
	value = ft_atoi(temp);
	free(temp);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

static int	convert_rgb(char *line)
{
	char	**rgb;
	int		color;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (-1);
	r = get_rgb_value(rgb[0]);
	g = get_rgb_value(rgb[1]);
	b = get_rgb_value(rgb[2]);
	free_split(rgb);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	color = (r * 65536) + (g * 256) + b;
	return (color);
}

int	parse_color_line_safe(char *line, t_config *config)
{
	char	*color_part;
	int		color_value;

	color_part = ft_strchr(line, ' ');
	if (!color_part)
	{
		printf("Erreur : ligne de couleur invalide.\n");
		return (0);
	}
	color_part += 1;
	color_part = ft_strtrim(color_part, " \t\n");
	color_value = convert_rgb(color_part);
	free(color_part);
	if (color_value == -1)
	{
		printf("Erreur : couleur invalide.\n");
		return (0);
	}
	if (line[0] == 'F')
		config->floor_color = color_value;
	else if (line[0] == 'C')
		config->ceiling_color = color_value;
	return (1);
}

int	parse_texture_line(char *line, t_config *config)
{
	char	*path;

	path = ft_strchr(line, ' ');
	if (!path)
	{
		printf("Erreur : ligne de texture invalide.\n");
		return (0);
	}
	path += 1;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (config->texture_north)
		{
			printf("Error\nDuplicate North texture definition\n");
			free(path);
			return (0);
		}
		config->texture_north = path;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (config->texture_south)
		{
			printf("Error\nDuplicate South texture definition\n");
			free(path);
			return (0);
		}
		config->texture_south = path;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (config->texture_west)
		{
			printf("Error\nDuplicate West texture definition\n");
			free(path);
			return (0);
		}
		config->texture_west = path;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (config->texture_est)
		{
			printf("Error\nDuplicate East texture definition\n");
			free(path);
			return (0);
		}
		config->texture_est = path;
	}
	else
	{
		free(path);
		return (0);
	}
	return (1);
}

void	parse_color_line(char *line, t_config *config)
{
	char	*color_part;
	int		color_value;

	color_part = ft_strchr(line, ' ');
	if (!color_part)
	{
		printf("Erreur : ligne de couleur invalide.\n");
		return ;
	}
	color_part += 1;
	color_part = ft_strtrim(color_part, " \t\n");
	color_value = convert_rgb(color_part);
	free(color_part);
	if (color_value == -1)
	{
		printf("Erreur : couleur invalide.\n");
		return ;
	}
	if (line[0] == 'F')
		config->floor_color = color_value;
	else if (line[0] == 'C')
		config->ceiling_color = color_value;
}
