#include <wolf3d.h>

/*
**	Цвет в формате HEX — это ни что иное, как шестнадцатеричное 
**	представление RGB.
*/

/*
**	Цвета представляются в виде трёх групп шестнадцатеричных цифр,
**	где каждая группа отвечает за свой цвет: #112233, где 11 — красный,
**	22 — зелёный, 33 — синий. Все значения должны быть между 00 и FF.
*/

/*
**	Во многих приложениях допускается сокращённая форма записи шестнадцатеричных
*/

/*
**	цветов. Если каждая из трёх групп содержит одинаковые 
**	символы, например #112233,
**	то их можно записать как #123.
*/

/*
**	h1 { color: #ff0000; } красный 
**	h2 { color: #00ff00; } зелёный
**	h3 { color: #0000ff; } синий h4 { color: #00f;}
*/

/*
**	https://colorscheme.ru/color-converter.html
*/

void	set_the_color_to_the_celing(int ray_nbr, t_cntnr *cntnr)
{
	int	y;

	y = 0;
	while (y < cntnr->wall_top_pixel)
	{
		cntnr->color_buffer[(WINDOW_WIDTH * y) + ray_nbr] = 0xFF333333;
		y++;
	}
}

void	calculate_texture_offset_x(int ray_nbr, t_cntnr *cntnr, t_ray *trays)
{
	if (trays[ray_nbr].was_hit_vrtcl)
		cntnr->txtre_offset_x = (int)trays[ray_nbr].wall_hit_y % TEXTURE_HEIGHT;
	else
		cntnr->txtre_offset_x = (int)trays[ray_nbr].wall_hit_x % TEXTURE_WIDTH;
}

void	set_the_color_to_the_bottom(int ray_nbr, t_cntnr *cntnr)
{
	int	y;

	y = cntnr->wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		cntnr->color_buffer[(WINDOW_WIDTH * y) + ray_nbr] = 0xff040461;
		y++;
	}
}

void	conteyner_for_gen_3d_proj(int i, t_cntnr *cntnr, t_ray *trays)
{
	set_the_color_to_the_celing(i, cntnr);
	calculate_texture_offset_x(i, cntnr, trays);
	get_correct_texture_id_depend_of_wall_dir(i, cntnr, trays);
	set_the_color_to_the_bottom(i, cntnr);
}

void	generate_3d_projection(t_cntnr *cntnr, t_player *plr, t_ray *trays)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		cntnr->perp_distance = trays[i].distance * cos(
				trays[i].ray_angle - plr->rotation_angle);
		cntnr->projected_wall_height = (
				TILE_SIZE / cntnr->perp_distance) * DIST_PROJ_PLANE;
		cntnr->wall_strip_height = (int)(cntnr->projected_wall_height);
		cntnr->wall_top_pixel = (
				WINDOW_HEIGHT / 2) - (cntnr->wall_strip_height / 2);
		if (cntnr->wall_top_pixel < 0)
			cntnr->wall_top_pixel = 0;
		else
			cntnr->wall_top_pixel = cntnr->wall_top_pixel;
		cntnr->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (
				cntnr->wall_strip_height / 2);
		if (cntnr->wall_bottom_pixel > WINDOW_HEIGHT)
			cntnr->wall_bottom_pixel = WINDOW_HEIGHT;
		else
			cntnr->wall_bottom_pixel = cntnr->wall_bottom_pixel;
		conteyner_for_gen_3d_proj(i, cntnr, trays);
		i++;
	}
}
