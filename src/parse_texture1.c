/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:43:15 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/10 22:43:17 by lsadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture_line(char *line)
{
	char	*trimmed;
	int		result;

	if (!line)
		return (0);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	result = 0;
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		result = 1;
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		result = 1;
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		result = 1;
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		result = 1;
	free(trimmed);
	return (result);
}

int	parse_texture_line(char *line, t_config *config)
{
	char	*path;
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	path = extract_texture_path(trimmed);
	if (!path)
	{
		free(trimmed);
		return (0);
	}
	if (!assign_texture_by_direction(config, path, trimmed))
	{
		free(path);
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

char	*extract_texture_path(char *trimmed)
{
	char	*path;

	path = ft_strchr(trimmed, ' ');
	if (!path)
	{
		printf("Erreur : ligne de texture invalide.\n");
		return (NULL);
	}
	path += 1;
	return (ft_strtrim(path, " \t\n"));
}
