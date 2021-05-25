/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremarqu <jremarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:40:08 by jremarqu          #+#    #+#             */
/*   Updated: 2021/05/25 18:21:26 by jremarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	destroy_window(t_cntnr *cntnr)
{
	free_wall_textures(cntnr);
	free(cntnr->color_buffer);
	SDL_DestroyTexture(cntnr->color_bffr_txtre);
	SDL_DestroyRenderer(cntnr->renderer);
	SDL_DestroyWindow(cntnr->window);
	SDL_Quit();
}

/*
**	SDL_RenderPresent - Update the screen with any rendering 
**		performed since the previous call.
**	https://wiki.libsdl.org/
*/

int	main(int argc, char **argv)
{
	t_cntnr		cntnr;
	t_player	plr;
	t_ray		trays[NUM_RAYS];

	if (argc != 2)
	{
		ft_putstr("./RTv map.txt\n");
		exit(1);
	}
	read_and_pars_file(&plr, argv[1]);
	check_num_of_cols(&plr);
	check_contain_of_map(&plr);
	translate_map_from_char_to_int(&plr);
	initializing_of_ctnr(&cntnr);
	cntnr.is_game_running = initializing_of_window(&cntnr);
	setup(&cntnr, &plr);
	while (cntnr.is_game_running)
	{
		process_input(&cntnr, &plr);
		update(&cntnr, &plr, trays);
		render(&cntnr, &plr, trays);
	}
	destroy_window(&cntnr);
	return (0);
}
