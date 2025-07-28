/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:56:38 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/28 13:11:08 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static t_coords get_delta_dist(float cos_angle, float sin_angle)
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

static int	get_step(float angle_op)
{
	if (angle_op < 0)
		return (-1);
	else
		return (1);
}

static float	get_side_dist(float angle_op, float start_grid, float map_pos, float delta)
{
	if (angle_op < 0)
		return ((start_grid - map_pos) * delta);
	else
		return ((map_pos + 1.0 - start_grid) * delta);
}

static void	jump_next_grid(t_coords *side_dist, t_coords delta_dist, t_coords *map_pos, t_coords step, int *side)
{
	// Which side is the nearest to a grid line
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist.x;
		map_pos->x += step.x;
		*side = 0;
	}
	else
	{
		side_dist->y += delta_dist.y;
		map_pos->y += step.y;
		*side = 1;
	}
}


static int check_collision_or_bounds(t_coords map_pos, t_map map)
{
	if (map_pos.x < 0 || map_pos.y < 0 || map_pos.y >= map.map_height)
		return (1);
	if (map_pos.x >= (int)ft_strlen(map.map[(int)map_pos.y]))
		return (1);
	return (0);
}

static void calc_impact(int side, t_coords map_pos, t_coords start, t_coords step, float cos_angle, float sin_angle, float *perp_wall_dist, t_coords *impact)
{
	int temp;
	
	if (step.x < 0)
		temp = 0;
	else
		temp = 1;
	if (side == 0)
	{
		*perp_wall_dist = (map_pos.x - (start.x / BLOCK) + (1 - step.x) / 2) / cos_angle;
		impact->x = (map_pos.x + temp) * BLOCK;
		impact->y = start.y + (*perp_wall_dist) * sin_angle * BLOCK;
	}
	else
	{
		*perp_wall_dist = (map_pos.y - (start.y / BLOCK) + (1 - step.y) / 2) / sin_angle;
		impact->x = start.x + (*perp_wall_dist) * cos_angle * BLOCK;
		impact->y = (map_pos.y + temp) * BLOCK;
	}
}
static void init_dda_vars(t_dda_vars *vars, t_coords start, float cos_angle, float sin_angle)
{
	vars->map_pos.x = (int)(start.x / BLOCK);
	vars->map_pos.y = (int)(start.y / BLOCK);
	vars->delta_dist = get_delta_dist(cos_angle, sin_angle);
	vars->step.x = get_step(cos_angle);
	vars->side_dist.x = get_side_dist(cos_angle, (start.x / BLOCK), vars->map_pos.x, vars->delta_dist.x);
	vars->step.y = get_step(sin_angle);
	vars->side_dist.y = get_side_dist(sin_angle, (start.y / BLOCK), vars->map_pos.y, vars->delta_dist.y);
}

t_ray	cast_ray_dda(t_coords start, float cos_angle, float sin_angle, t_map map)
{
	t_ray       result;
	t_dda_vars	vars;
	int			hit;
	int			side;
	float		perp_wall_dist;

	result.ray = start;
	result.dir.x = cos_angle;
	result.dir.y = sin_angle;
	init_dda_vars(&vars, start, cos_angle, sin_angle);
	hit = 0;
	while (!hit)
	{
		jump_next_grid(&vars.side_dist, vars.delta_dist, &vars.map_pos, vars.step, &side);
		if (check_collision_or_bounds(vars.map_pos, map))
			break;
		if (map.map[(int)vars.map_pos.y][(int)vars.map_pos.x] == WALL)
			hit = 1;
	}
	calc_impact(side, vars.map_pos, start, vars.step, cos_angle, sin_angle, &perp_wall_dist, &result.impact);
	result.relative.x = perp_wall_dist * BLOCK;
	result.relative.y = 0;
	result.ray.x = side;
	return (result);
}
