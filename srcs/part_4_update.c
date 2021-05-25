#include <wolf3d.h>

void	move_player(float deltaTime, t_player *plr)
{
	float	moveStep;
	float	newPlayerX;
	float	newPlayerY;

	plr->rotation_angle += plr->turn_dir * plr->turn_speed * deltaTime;
	moveStep = plr->walk_dir * plr->walk_speed * deltaTime;
	newPlayerX = plr->x + cos(plr->rotation_angle) * moveStep;
	newPlayerY = plr->y + sin(plr->rotation_angle) * moveStep;
	if (!map_has_wall_at(newPlayerX, newPlayerY, plr))
	{
		plr->x = newPlayerX;
		plr->y = newPlayerY;
	}
}

/*
**	waste some time until we reach the target frame time length
*/

void	update(t_cntnr *cntnr, t_player *plr, t_ray *tray)
{
	float	deltaTime;

	if (!SDL_TICKS_PASSED(SDL_GetTicks(),
			cntnr->ticks_last_frame + FRAME_TIME_LENGTH))
		return ;
	deltaTime = (SDL_GetTicks() - cntnr->ticks_last_frame) / 1000.0f;
	cntnr->ticks_last_frame = SDL_GetTicks();
	move_player(deltaTime, plr);
	cast_all_rays(plr, tray);
}
