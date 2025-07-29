/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_impact.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:57:03 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 14:13:34 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_vertical_impact(t_calc_data data, float cos_angle,
		float sin_angle, t_ray *result)
{
	int		temp;
	float	perp_wall_dist;

	if (data.step.x < 0)
		temp = 0;
	else
		temp = 1;
	perp_wall_dist = (data.map_pos.x - (data.start.x / BLOCK) + (1
				- data.step.x) / 2) / cos_angle;
	result->impact.x = (data.map_pos.x + temp) * BLOCK;
	result->impact.y = data.start.y + perp_wall_dist * sin_angle * BLOCK;
	result->relative.x = perp_wall_dist * BLOCK;
}

static void	calc_horizontal_impact(t_calc_data data, float cos_angle,
		float sin_angle, t_ray *result)
{
	int		temp;
	float	perp_wall_dist;

	if (data.step.y < 0)
		temp = 0;
	else
		temp = 1;
	perp_wall_dist = (data.map_pos.y - (data.start.y / BLOCK) + (1
				- data.step.y) / 2) / sin_angle;
	result->impact.x = data.start.x + perp_wall_dist * cos_angle * BLOCK;
	result->impact.y = (data.map_pos.y + temp) * BLOCK;
	result->relative.x = perp_wall_dist * BLOCK;
}

void	calc_impact(int side, t_coords start, t_dda_vars vars,
		t_ray *result)
{
	t_calc_data	data;
	float		cos_angle;
	float		sin_angle;

	data.map_pos = vars.map_pos;
	data.start = start;
	data.step = vars.step;
	data.side = side;
	cos_angle = result->dir.x;
	sin_angle = result->dir.y;
	if (side == VERTICAL_HIT)
		calc_vertical_impact(data, cos_angle, sin_angle, result);
	else
		calc_horizontal_impact(data, cos_angle, sin_angle, result);
}
