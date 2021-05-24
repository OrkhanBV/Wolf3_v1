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
			cntnr->colorBuffer[(WINDOW_WIDTH * y) + x] = color;
			y++;
		}
		x++;
	}
}

void	render_color_buffer(t_cntnr *cntnr)
{
	SDL_UpdateTexture(
		cntnr->colorBufferTexture,
		NULL,
		cntnr->colorBuffer,
		(int)(WINDOW_WIDTH * sizeof(uint32_t)));
	SDL_RenderCopy(cntnr->renderer, cntnr->colorBufferTexture, NULL, NULL);
}
