/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_1_initialization_and_setup.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremarqu <jremarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 02:08:13 by jremarqu          #+#    #+#             */
/*   Updated: 2021/05/25 19:08:03 by jremarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	initializing_of_ctnr(t_cntnr *cntnr)
{
	cntnr->is_game_running = FALSE;
	cntnr->window = NULL;
	cntnr->renderer = NULL;
	cntnr->is_game_running = FALSE;
	cntnr->ticks_last_frame = 0;
	cntnr->color_buffer = NULL;
	cntnr->color_bffr_txtre = NULL;
}

int	initializing_of_window(t_cntnr *cntnr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return (FALSE);
	}
	cntnr->window = SDL_CreateWindow(
			NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
			WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!(cntnr->window))
	{
		fprintf(stderr, "Error creating SDL window.\n");
		return (FALSE);
	}
	cntnr->renderer = SDL_CreateRenderer(cntnr->window, -1, 0);
	if (!(cntnr->renderer))
	{
		fprintf(stderr, "Error creating SDL renderer.\n");
		return (FALSE);
	}
	SDL_SetRenderDrawBlendMode(cntnr->renderer, SDL_BLENDMODE_BLEND);
	return (TRUE);
}

/*
**	1)manually create a blue texture with black  
**	pixels in every x & y multiples of 8
*/

/*
**	2)load some textures from the textures.h
**	3)allocate the total amount of bytes in memory to hold our colorbuffer
*/

/*
**	4)create an SDL_Texture to display the colorbuffer
**	5)manually create a blue texture with black pixels 
** in every x & y multiples of 8
*/

/*
**						MAP CENTER
**		plr->x = TILE_SIZE * 9 + TILE_SIZE / 2;
**		plr->y = TILE_SIZE * 6 + TILE_SIZE / 2;
*/

/*
** https://wiki.libsdl.org/SDL_CreateTexture
** SDL_CreateTexture & Uint_32
*/

void	init_way_to_png(t_cntnr *cntnr)
{
	cntnr->texture_fl_names[0] = "includes/img/bluestone.png";
	cntnr->texture_fl_names[1] = "includes/img/graystone.png";
	cntnr->texture_fl_names[2] = "includes/img/colorstone.png";
	cntnr->texture_fl_names[3] = "includes/img/mossystone.png";
}

void	setup(t_cntnr *cntnr, t_player *plr)
{
	plr->x = TILE_SIZE * 9 + TILE_SIZE / 2;
	plr->y = TILE_SIZE * 6 + TILE_SIZE / 2;
	plr->width = 3;
	plr->height = 3;
	plr->turn_dir = 0;
	plr->walk_dir = 0;
	plr->rotation_angle = PI;
	plr->walk_speed = 200;
	plr->turn_speed = 200 * (PI / 180);
	cntnr->color_buffer = (uint32_t *)malloc(
			sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
	cntnr->color_bffr_txtre = SDL_CreateTexture(
			cntnr->renderer,
			SDL_PIXELFORMAT_ABGR8888,
			SDL_TEXTUREACCESS_STREAMING,
			WINDOW_WIDTH,
			WINDOW_HEIGHT);
	init_way_to_png(cntnr);
	load_wall_textures(cntnr);
}
