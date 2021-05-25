#include <wolf3d.h>

void	clear_color_buffer(uint32_t color, t_cntnr *cntnr)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			cntnr->color_buffer[(WINDOW_WIDTH * y) + x] = color;
			y++;
		}
		x++;
	}
}

void	render_color_buffer(t_cntnr *cntnr)
{
	SDL_UpdateTexture(
		cntnr->color_bffr_txtre,
		NULL,
		cntnr->color_buffer,
		(int)(WINDOW_WIDTH * sizeof(uint32_t)));
	SDL_RenderCopy(cntnr->renderer, cntnr->color_bffr_txtre, NULL, NULL);
}
