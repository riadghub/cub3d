/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:41:55 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:42:00 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(t_data *data, int line_index)
{
	int		j;
	char	*line;
	int		len;

	line = data->map[line_index];
	len = ft_str_len(line);
	if (len < 3)
		return (0);
	j = 0;
	while (line[j])
	{
		if (line[j] != '1' && line[j] != ' ')
			return (0);
		j++;
	}
	return (1);
}
