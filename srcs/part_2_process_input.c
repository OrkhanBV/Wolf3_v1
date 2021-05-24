#include <wolf3d.h>

void	press_key_button(SDL_Event event, t_player *plr, t_cntnr *cntnr)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		cntnr->isGameRunning = FALSE;
	if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
		plr->walk_dir = +1;
	if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
		plr->walk_dir = -1;
	if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
		plr->turn_dir = +1;
	if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
		plr->turn_dir = -1;
}

void	unpress_key_button(SDL_Event event, t_player *plr)
{
	if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
		plr->walk_dir = 0;
	if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
		plr->walk_dir = 0;
	if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
		plr->turn_dir = 0;
	if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
		plr->turn_dir = 0;
}

void	process_input(t_cntnr *cntnr, t_player *plr)
{
	SDL_Event	event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		cntnr->isGameRunning = FALSE;
	else if (event.type == SDL_KEYDOWN)
		press_key_button(event, plr, cntnr);
	else if (event.type == SDL_KEYUP)
		unpress_key_button(event, plr);
}
