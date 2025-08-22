double	ray_cast(int x, t_player *player, t_ray *ray)
{
	double camera_x;
	double side_dist_x, side_dist_y;
	double perp_wall_dist;
	int hit = 0;
	int side;

	// Calculate ray position and direction
	camera_x = 2 * x / (double)WIN_WIDTH - 1; // x-coordinate in camera space
	ray->ray_dir.x = player->vector_dir.x + player->camera_plane.x * camera_x;
	ray->ray_dir.y = player->vector_dir.y + player->camera_plane.y * camera_x;

	// Which box of the map we're in
	ray->map_x = (int)player->player_pos.x;
	ray->map_y = (int)player->player_pos.y;

	// Length of ray from current position to x or y side
	ray->delta.x = fabs(1 / ray->ray_dir.x);
	ray->delta.y = fabs(1 / ray->ray_dir.y);

	// Calculate step and initial sideDist
	if (ray->ray_dir.x < 0)
	{
		ray->step_dir_x = -1;
		side_dist_x = (player->player_pos.x - ray->map_x) * ray->delta.x;
	}
	else
	{
		ray->step_dir_x = 1;
		side_dist_x = (ray->map_x + 1.0 - player->player_pos.x) * ray->delta.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_dir_y = -1;
		side_dist_y = (player->player_pos.y - ray->map_y) * ray->delta.y;
	}
	else
	{
		ray->step_dir_y = 1;
		side_dist_y = (ray->map_y + 1.0 - player->player_pos.y) * ray->delta.y;
	}

	// Perform DDA
	while (hit == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += ray->delta.x;
			ray->map_x += ray->step_dir_x;
			side = 0;
		}
		else
		{
			side_dist_y += ray->delta.y;
			ray->map_y += ray->step_dir_y;
			side = 1;
		}
		// Check if ray has hit a wall
		// Note: You'll need to implement your map checking here
		// For now, assuming a simple condition
		-you should replace this with your actual map data if (ray->map_x < 0
				|| ray->map_x >= 24 || ray->map_y < 0
				|| ray->map_y >= 24) hit = 1;
		// Hit boundary (replace with your map checking logic)
	}

	// Calculate distance projected on camera direction
	if (side == 0)
		perp_wall_dist = (ray->map_x - player->player_pos.x + (1
					- ray->step_dir_x) / 2) / ray->ray_dir.x;
	else
		perp_wall_dist = (ray->map_y - player->player_pos.y + (1
					- ray->step_dir_y) / 2) / ray->ray_dir.y;

	ray->wall_hit = side;
	return (perp_wall_dist);
}