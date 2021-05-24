#include <wolf3d.h>

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

void	initialization_for_cast_ray(float ray_angle, t_ray *trays)
{
	if (ray_angle > 0 && ray_angle < PI)
		trays->is_ray_facing_down = 1;
	else
		trays->is_ray_facing_down = 0;
	if (!(trays->is_ray_facing_down))
		trays->is_ray_facing_up = 1;
	else
		trays->is_ray_facing_up = 0;
	if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)
		trays->is_ray_facing_right = 1;
	else
		trays->is_ray_facing_right = 0;
	if (!(trays->is_ray_facing_right))
		trays->is_ray_facing_left = 1;
	else
		trays->is_ray_facing_left = 0;
}

void	cast_ray(float ray_angle, int stripId, t_player *plr, t_ray *trays)
{
	ray_angle = normalize_angle(ray_angle);
	initialization_for_cast_ray(ray_angle, trays);
	horizontal_ray_grid_intersection_main(ray_angle, plr, trays);
	hor_increment_x_y_step_until_a_wall(plr, trays);
	intialization_before_estimates_ver(trays);
	verical_ray_grid_intersection_main(ray_angle, plr, trays);
	vert_increment_x_y_step_until_a_wall(plr, trays);
	find_the_closer_distance_of_hit_vert_or_hor(stripId, plr, trays);
	trays[stripId].ray_angle = ray_angle;
	trays[stripId].is_ray_facing_down = trays->is_ray_facing_down;
	trays[stripId].is_ray_facing_up = trays->is_ray_facing_up;
	trays[stripId].is_ray_facing_left = trays->is_ray_facing_left;
	trays[stripId].is_ray_facing_right = trays->is_ray_facing_right;
}

void	cast_all_rays(t_player *plr, t_ray *tray)
{
	int		col;
	float	ray_angle;

	col = 0;
	ray_angle = 0.0;
	while (col < NUM_RAYS)
	{
		ray_angle = plr->rotation_angle + atan(
				(col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		cast_ray(ray_angle, col, plr, tray);
		col++;
	}
}
