/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:51:47 by okoca             #+#    #+#             */
/*   Updated: 2024/08/03 09:01:09 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	cb_rt_set(t_ctx *ctx)
{
	t_raytracer	raytracer;
	t_player	player;

	player = ctx->map.player;
	raytracer = ctx->raytracer;
	raytracer.vec.y = 0;
	raytracer.camera_x = 2 * (double)raytracer.vec.x / SCREEN_WIDTH - 1;
	raytracer.ray_dir.x = player.dir.x + player.plane.x * raytracer.camera_x;
	raytracer.ray_dir.y = player.dir.y + player.plane.y * raytracer.camera_x;
	raytracer.map_check.x = (int)player.pos.x;
	raytracer.map_check.y = (int)player.pos.y;
	if (raytracer.ray_dir.x == 0)
		raytracer.delta_dist.x = 1e30;
	else
		raytracer.delta_dist.x = fabs(1 / raytracer.ray_dir.x);
	if (raytracer.ray_dir.y == 0)
		raytracer.delta_dist.y = 1e30;
	else
		raytracer.delta_dist.y = fabs(1 / raytracer.ray_dir.y);
	raytracer.distance_to_wall = 0;
	raytracer.hit = 0;
	raytracer.orientation = 0;
	ctx->raytracer = raytracer;
}

inline void	cb_side_step(t_ctx *ctx)
{
	t_player	p;
	t_raytracer	*rt;

	rt = &ctx->raytracer;
	p = ctx->map.player;
	if (rt->ray_dir.x < 0)
	{
		rt->step.x = -1;
		rt->side_dist.x = (p.pos.x - rt->map_check.x) * rt->delta_dist.x;
	}
	else
	{
		rt->step.x = 1;
		rt->side_dist.x = (rt->map_check.x + 1.0 - p.pos.x) * rt->delta_dist.x;
	}
	if (rt->ray_dir.y < 0)
	{
		rt->step.y = -1;
		rt->side_dist.y = (p.pos.y - rt->map_check.y) * rt->delta_dist.y;
	}
	else
	{
		rt->step.y = 1;
		rt->side_dist.y = (rt->map_check.y + 1.0 - p.pos.y) * rt->delta_dist.y;
	}
}

inline void	cb_check_hit(t_ctx *ctx)
{
	t_raytracer	*rt;
	t_map		map;

	rt = &ctx->raytracer;
	map = ctx->map;
	while (rt->hit == 0)
	{
		if (rt->side_dist.x < rt->side_dist.y)
		{
			rt->side_dist.x += rt->delta_dist.x;
			rt->map_check.x += rt->step.x;
			rt->side = 0;
		}
		else
		{
			rt->side_dist.y += rt->delta_dist.y;
			rt->map_check.y += rt->step.y;
			rt->side = 1;
		}
		if (rt->map_check.x > map.width || rt->map_check.y > map.height)
			rt->hit = 1;
		else if (map.map[rt->map_check.y][rt->map_check.x] == '1')
			rt->hit = 1;
	}
}

inline void	cb_wall_dist(t_ctx *ctx)
{
	t_raytracer	*rt;

	rt = &ctx->raytracer;
	if (rt->side == 0)
	{
		if (rt->ray_dir.x > 0)
			rt->orientation = EAST;
		else
			rt->orientation = WEST;
		rt->distance_to_wall = (rt->side_dist.x - rt->delta_dist.x);
	}
	else
	{
		rt->distance_to_wall = (rt->side_dist.y - rt->delta_dist.y);
		if (rt->ray_dir.y > 0)
			rt->orientation = SOUTH;
		else
			rt->orientation = NORTH;
	}
}
