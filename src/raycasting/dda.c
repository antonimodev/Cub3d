/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:56:38 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 14:19:38 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	jump_next_grid(t_dda_vars *vars, int *side)
{
	if (vars->side_dist.x < vars->side_dist.y)
	{
		vars->side_dist.x += vars->delta_dist.x;
		vars->map_pos.x += vars->step.x;
		*side = 0;
	}
	else
	{
		vars->side_dist.y += vars->delta_dist.y;
		vars->map_pos.y += vars->step.y;
		*side = 1;
	}
}

static int	check_collision_or_bounds(t_coords map_pos, t_map map)
{
	if (map_pos.x < 0 || map_pos.y < 0 || map_pos.y >= map.map_height)
		return (1);
	if (map_pos.x >= (int)ft_strlen(map.map[(int)map_pos.y]))
		return (1);
	return (0);
}

t_ray	cast_ray_dda(t_coords start, float cos_angle, float sin_angle,
		t_map map)
{
	t_ray		result;
	t_dda_vars	vars;
	int			hit;
	int			side;

	result.ray = start;
	result.dir.x = cos_angle;
	result.dir.y = sin_angle;
	init_dda_vars(&vars, start, cos_angle, sin_angle);
	hit = 0;
	while (!hit)
	{
		jump_next_grid(&vars, &side);
		if (check_collision_or_bounds(vars.map_pos, map))
			break ;
		if (map.map[(int)vars.map_pos.y][(int)vars.map_pos.x] == WALL)
			hit = 1;
	}
	calc_impact(side, start, vars, &result);
	result.relative.y = 0;
	result.ray.x = side;
	return (result);
}
