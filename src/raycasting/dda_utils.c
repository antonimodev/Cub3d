/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:07:57 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 14:20:34 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_step(float angle_op)
{
	if (angle_op < 0)
		return (-1);
	else
		return (1);
}

static t_coords	get_delta_dist(float cos_angle, float sin_angle)
{
	t_coords	delta_dist;

	if (cos_angle == 0)
		delta_dist.x = INFINITE;
	else
		delta_dist.x = fabs(1.0 / cos_angle);
	if (sin_angle == 0)
		delta_dist.y = INFINITE;
	else
		delta_dist.y = fabs(1.0 / sin_angle);
	return (delta_dist);
}

static float	get_side_dist(float angle_op, float start_grid, float map_pos,
		float delta)
{
	if (angle_op < 0)
		return ((start_grid - map_pos) * delta);
	else
		return ((map_pos + 1.0 - start_grid) * delta);
}

void	init_dda_vars(t_dda_vars *vars, t_coords start, float cos_angle,
		float sin_angle)
{
	vars->map_pos.x = (int)(start.x / BLOCK);
	vars->map_pos.y = (int)(start.y / BLOCK);
	vars->delta_dist = get_delta_dist(cos_angle, sin_angle);
	vars->step.x = get_step(cos_angle);
	vars->side_dist.x = get_side_dist(cos_angle, (start.x / BLOCK),
			vars->map_pos.x, vars->delta_dist.x);
	vars->step.y = get_step(sin_angle);
	vars->side_dist.y = get_side_dist(sin_angle, (start.y / BLOCK),
			vars->map_pos.y, vars->delta_dist.y);
}
