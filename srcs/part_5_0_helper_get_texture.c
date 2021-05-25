#include <wolf3d.h>

void	set_texture_by_nbr(int y, int ray_nbr, t_cntnr *cntnr, int nbr_of_text)
{
	cntnr->texel_color = cntnr->wall_textures[nbr_of_text].texture_buffer[(
			TEXTURE_WIDTH * cntnr->txtre_offset_y) + cntnr->txtre_offset_x];
	cntnr->color_buffer[(WINDOW_WIDTH * y) + ray_nbr] = cntnr->texel_color;
}

void	switch_case_for_get_correct_texture(int y, int ray_nbr,
		t_cntnr *cntnr, t_ray *trays)
{
	if (trays[ray_nbr].is_ray_facing_up
		&& trays[ray_nbr].was_hit_vrtcl != 1)
		set_texture_by_nbr(y, ray_nbr, cntnr, 0);
	else if (trays[ray_nbr].is_ray_facing_left
		&& trays[ray_nbr].was_hit_vrtcl)
		set_texture_by_nbr(y, ray_nbr, cntnr, 1);
	else if (trays[ray_nbr].is_ray_facing_right
		&& trays[ray_nbr].was_hit_vrtcl)
		set_texture_by_nbr(y, ray_nbr, cntnr, 2);
	else if (trays[ray_nbr].is_ray_facing_down
		&& trays[ray_nbr].was_hit_vrtcl != 1)
		set_texture_by_nbr(y, ray_nbr, cntnr, 3);
}

void	get_correct_texture_id_depend_of_wall_dir(int ray_nbr,
		t_cntnr *cntnr, t_ray *trays)
{
	int	y;

	y = cntnr->wall_top_pixel;
	while (y < cntnr->wall_bottom_pixel)
	{
		cntnr->distance_from_top = y + (
				cntnr->wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
		cntnr->txtre_offset_y = cntnr->distance_from_top * (
				(float)TEXTURE_HEIGHT / cntnr->wall_strip_height);
		switch_case_for_get_correct_texture(y, ray_nbr, cntnr, trays);
		y++;
	}
}
