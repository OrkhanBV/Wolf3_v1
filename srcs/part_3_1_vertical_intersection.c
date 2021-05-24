#include <wolf3d.h>

void	intialization_before_estimates_ver(t_ray *trays)
{
	trays->found_vert_wall_hit = FALSE;
	trays->vert_wall_hit_x = 0;
	trays->vert_wall_hit_y = 0;
	trays->vert_wall_content = 0;
}

void	verical_ray_grid_intersection_main(float ray_angle, t_player *plr,
	t_ray *trays)
{
	trays->xintercept = floor(plr->x / TILE_SIZE) * TILE_SIZE;
	if (trays->is_ray_facing_right)
		trays->xintercept += TILE_SIZE;
	else
		trays->xintercept += 0;
	trays->yintercept = plr->y + (trays->xintercept - plr->x) * tan(ray_angle);
	trays->xstep = TILE_SIZE;
	if (trays->is_ray_facing_left)
		trays->xstep *= -1;
	else
		trays->xstep *= 1;
	trays->ystep = TILE_SIZE * tan(ray_angle);
	if (trays->is_ray_facing_up && trays->ystep > 0)
		trays->ystep *= -1;
	else
		trays->ystep *= 1;
	if (trays->is_ray_facing_down && trays->ystep < 0)
		trays->ystep *= -1;
	else
		trays->ystep *= 1;
	trays->next_vert_touch_x = trays->xintercept;
	trays->next_vert_touch_y = trays->yintercept;
}

void	vert_increment_x_y_step_until_a_wall(t_player *plr, t_ray *trays)
{
	while (trays->next_vert_touch_x >= 0 && trays->next_vert_touch_y >= 0
		&& trays->next_vert_touch_x <= WINDOW_WIDTH
		&& trays->next_vert_touch_y <= WINDOW_HEIGHT)
	{
		if (trays->is_ray_facing_left)
			trays->x_to_check = trays->next_vert_touch_x - 1;
		else
			trays->x_to_check = trays->next_vert_touch_x + 0;
		trays->y_to_check = trays->next_vert_touch_y;
		if (map_has_wall_at(trays->x_to_check, trays->y_to_check, plr))
		{
			trays->vert_wall_hit_x = trays->next_vert_touch_x;
			trays->vert_wall_hit_y = trays->next_vert_touch_y;
			trays->vert_wall_content = plr->map[
				(int)floor(trays->y_to_check / TILE_SIZE)]
			[(int)floor(trays->x_to_check / TILE_SIZE)];
			trays->found_vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			trays->next_vert_touch_x += trays->xstep;
			trays->next_vert_touch_y += trays->ystep;
		}
	}
}
