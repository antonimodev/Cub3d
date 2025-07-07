/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:43:10 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/07 11:43:50 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_flood_fill(int x, int y, char **map)
{
	int	rows;
	int	cols;

	rows = matrix_len(map);
	if (x < 0 || x >= rows || !map[x])
		return (false);
	cols = ft_strlen(map[x]);
	if (y < 0 || y >= cols)
		return (false);
	if (map[x][y] == ' ')
		return (false);
	if (map[x][y] == '1' || map[x][y] == 'V')
		return (true);
	map[x][y] = 'V';
	if (!validate_flood_fill(x + 1, y, map)
		|| !validate_flood_fill(x - 1, y, map)
		|| !validate_flood_fill(x, y + 1, map)
		|| !validate_flood_fill(x, y - 1, map))
		return (false);
	return (true);
}
