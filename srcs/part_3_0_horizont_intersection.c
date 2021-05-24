#include <wolf3d.h>

int	map_has_wall_at(float x, float y, t_player *plr)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (TRUE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (plr->map[map_grid_index_y][map_grid_index_x] != 0)
		return (plr->map[map_grid_index_y][map_grid_index_x]);
	else
		return (0);
}

void	intialization_before_estimates_hor(t_ray *trays)
{
	trays->found_horz_wall_hit = FALSE;
	trays->horz_wall_hit_x = 0;
	trays->horz_wall_hit_y = 0;
	trays->horz_wall_content = 0;
}

void	hor_increment_x_y_step_until_a_wall(t_player *plr, t_ray *trays)
{
	while (trays->next_horz_touch_x >= 0 && trays->next_horz_touch_y >= 0
		&& trays->next_horz_touch_x <= WINDOW_WIDTH
		&& trays->next_horz_touch_y <= WINDOW_HEIGHT)
	{
		trays->x_to_check = trays->next_horz_touch_x;
		if (trays->is_ray_facing_up)
			trays->y_to_check = trays->next_horz_touch_y - 1;
		else
			trays->y_to_check = trays->next_horz_touch_y + 0;
		if (map_has_wall_at(trays->x_to_check, trays->y_to_check, plr))
		{
			trays->horz_wall_hit_x = trays->next_horz_touch_x;
			trays->horz_wall_hit_y = trays->next_horz_touch_y;
			trays->horz_wall_content = plr->map[(int)floor(
					trays->y_to_check / TILE_SIZE)][(int)floor(
					trays->x_to_check / TILE_SIZE)];
			trays->found_horz_wall_hit = TRUE;
			break ;
		}
		else
		{
			trays->next_horz_touch_x += trays->xstep;
			trays->next_horz_touch_y += trays->ystep;
		}
	}
}

/*
**	///////////////////////////////////////////
**	// HORIZONTAL RAY-GRID INTERSECTION CODE //
**	///////////////////////////////////////////
*/

void	horizontal_ray_grid_intersection_main(float ray_angle,
		t_player *plr, t_ray *trays)
{
	intialization_before_estimates_hor(trays);
	trays->yintercept = floor(plr->y / TILE_SIZE) * TILE_SIZE;
	if (trays->is_ray_facing_down == 0)
		trays->yintercept += 0;
	else
		trays->yintercept += TILE_SIZE;
	trays->xintercept = plr->x + (trays->yintercept - plr->y) / tan(ray_angle);
	trays->ystep = TILE_SIZE;
	if (trays->is_ray_facing_up == 0)
		trays->ystep *= 1;
	else
		trays->ystep *= -1;
	trays->xstep = TILE_SIZE / tan(ray_angle);
	if (trays->is_ray_facing_left && trays->xstep > 0)
		trays->xstep *= -1;
	else
		trays->xstep *= 1;
	if (trays->is_ray_facing_right && trays->xstep < 0)
		trays->xstep *= -1;
	else
		trays->xstep *= 1;
	trays->next_horz_touch_x = trays->xintercept;
	trays->next_horz_touch_y = trays->yintercept;
}
