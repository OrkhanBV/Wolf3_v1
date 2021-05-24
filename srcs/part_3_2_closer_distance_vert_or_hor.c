#include <wolf3d.h>

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	inner_case_one_for_d_h_v_or_h(int stripId, t_ray *trays)
{
	trays[stripId].distance = trays->vert_hit_distance;
	trays[stripId].wall_hit_x = trays->vert_wall_hit_x;
	trays[stripId].wall_hit_y = trays->vert_wall_hit_y;
	trays[stripId].wall_hit_content = trays->vert_wall_content;
	trays[stripId].was_hit_vrtcl = TRUE;
}

void	inner_case_two_for_d_h_v_or_h(int stripId, t_ray *trays)
{
	trays[stripId].distance = trays->horz_hit_distance;
	trays[stripId].wall_hit_x = trays->horz_wall_hit_x;
	trays[stripId].wall_hit_y = trays->horz_wall_hit_y;
	trays[stripId].wall_hit_content = trays->horz_wall_content;
	trays[stripId].was_hit_vrtcl = FALSE;
}

void	find_the_closer_distance_of_hit_vert_or_hor(
		int stripId, t_player *plr, t_ray *trays)
{
	if (trays->found_horz_wall_hit)
		trays->horz_hit_distance = distance_between_points(
				plr->x, plr->y, trays->horz_wall_hit_x, trays->horz_wall_hit_y);
	else
		trays->horz_hit_distance = FLT_MAX;
	if (trays->found_vert_wall_hit)
		trays->vert_hit_distance = distance_between_points(
				plr->x, plr->y, trays->vert_wall_hit_x, trays->vert_wall_hit_y);
	else
		trays->vert_hit_distance = FLT_MAX;
	if (trays->vert_hit_distance < trays->horz_hit_distance)
		inner_case_one_for_d_h_v_or_h(stripId, trays);
	else
		inner_case_two_for_d_h_v_or_h(stripId, trays);
}
