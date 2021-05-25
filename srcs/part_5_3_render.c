#include "wolf3d.h"

/*
**  brief A rectangle, with the origin at the upper left (integer).
**  A structure that contains the definition of a rectangle, with 
*/

/*
**	the origin at the upper left.
**  Data Fields
*/

/*
**  x the x location of the rectangle's upper left corner
**  y the y location of the rectangle's upper left corner
*/

/*
**  w the width of the rectangle
**  h the height of the rectangle
*/

/*
** typedef struct	SDL_Rect
** {
**		int x, y;
**		int w, h;
** }				SDL_Rect;
*/

/*
** SDL_RenderFillRect Fill a rectangle on the current 
** rendering target with the drawing color.
**
** the SDL_Rect structure representing the rectangle to fill, 
** or NULL for the entire rendering target
*/

void	setup_the_map_parameters(t_cntnr *cntnr)
{
	cntnr->map_tile_rect.x = cntnr->tile_x * MINIMAP_SCALE_FACTOR;
	cntnr->map_tile_rect.y = cntnr->tile_y * MINIMAP_SCALE_FACTOR;
	cntnr->map_tile_rect.w = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	cntnr->map_tile_rect.h = TILE_SIZE * MINIMAP_SCALE_FACTOR;
}

void	render_map(t_cntnr *cntnr, t_player *plr)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			cntnr->tile_x = j * TILE_SIZE;
			cntnr->tile_y = i * TILE_SIZE;
			if (plr->map[i][j] != 0)
				cntnr->tile_color = 255;
			else
				cntnr->tile_color = 0;
			SDL_SetRenderDrawColor(cntnr->renderer, cntnr->tile_color,
				cntnr->tile_color, cntnr->tile_color, 80);
			setup_the_map_parameters(cntnr);
			SDL_RenderFillRect(cntnr->renderer, &(cntnr->map_tile_rect));
			j++;
		}
		i++;
	}
}

void	render_rays(t_cntnr *cntnr, t_player *plr, t_ray *tray)
{
	int	i;

	i = 0;
	SDL_SetRenderDrawColor(cntnr->renderer, 255, 255, 0, 150);
	while (i < NUM_RAYS)
	{
		SDL_RenderDrawLine(cntnr->renderer,
			MINIMAP_SCALE_FACTOR * plr->x,
			MINIMAP_SCALE_FACTOR * plr->y,
			MINIMAP_SCALE_FACTOR * tray[i].wall_hit_x,
			MINIMAP_SCALE_FACTOR * tray[i].wall_hit_y
			);
		i++;
	}
}

void	render_player(t_cntnr *cntnr, t_player *plr)
{
	SDL_Rect	playerRect;

	SDL_SetRenderDrawColor(cntnr->renderer, 255, 255, 255, 255);
	playerRect.x = plr->x * MINIMAP_SCALE_FACTOR;
	playerRect.y = plr->y * MINIMAP_SCALE_FACTOR;
	playerRect.w = plr->width * MINIMAP_SCALE_FACTOR;
	playerRect.h = plr->height * MINIMAP_SCALE_FACTOR;
	SDL_RenderFillRect(cntnr->renderer, &playerRect);
	SDL_RenderDrawLine(
		cntnr->renderer,
		MINIMAP_SCALE_FACTOR * plr->x,
		MINIMAP_SCALE_FACTOR * plr->y,
		MINIMAP_SCALE_FACTOR * plr->x + cos(plr->rotation_angle) * 40,
		MINIMAP_SCALE_FACTOR * plr->y + sin(plr->rotation_angle) * 40
		);
}

/*
**  SDL_RenderPresent - Update the screen with any rendering 
**      performed since the previous call.
*/

void	render(t_cntnr *cntnr, t_player *plr, t_ray *trays)
{
	SDL_SetRenderDrawColor(cntnr->renderer, 0, 0, 0, 255);
	SDL_RenderClear(cntnr->renderer);
	generate_3d_projection(cntnr, plr, trays);
	render_color_buffer(cntnr);
	clear_color_buffer(0xFF000000, cntnr);
	render_map(cntnr, plr);
	render_rays(cntnr, plr, trays);
	render_player(cntnr, plr);
	SDL_RenderPresent(cntnr->renderer);
}
