/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremarqu <jremarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 00:49:23 by jremarqu          #+#    #+#             */
/*   Updated: 2021/05/25 18:25:53 by jremarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <SDL2/SDL.h>
# include <SDL.h>
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "libft/libft.h"
# include "upng.h"

# define FALSE 0
# define TRUE 1
# define FPS 30
# define FRAME_TIME_LENGTH 33.333333
/*
** FRAME_TIME_LENGTH (1000 / FPS)
*/
# define PI 3.14159265
# define TWO_PI 6.28318530
# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20
# define MAP_CRUDE_NUM_COLS 21
# define NUM_TEXTURES 8
# define MINIMAP_SCALE_FACTOR 0.3
# define WINDOW_WIDTH 1280
# define TEXTURENUM 16
# define TEXTURE_NBR 4
/*
** WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
*/
# define WINDOW_HEIGHT 832
/*
** WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
*/
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define FOV_ANGLE 1.04719755
/*
** FOV_ANGLE = (60 * (3.14159265 / 180))
*/
# define NUM_RAYS WINDOW_WIDTH
# define DIST_PROJ_PLANE 1108.801108
/*
** DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2)) tan(0.5235)
*/

typedef struct s_player
{
	float		x;
	float		y;
	float		width;
	float		height;
	int			turn_dir;
	int			walk_dir;
	float		rotation_angle;
	float		walk_speed;
	float		turn_speed;
	int			map[MAP_NUM_ROWS][MAP_NUM_COLS];
	char		crude_map[MAP_NUM_ROWS + 1][MAP_NUM_COLS + 1];
}				t_player;

/*
**	int		turn_dir; -1 for left, +1 for right
**	int		walk_dir; -1 for back, +1 for front
*/

typedef struct s_ray
{
	float			ray_angle;
	float			wall_hit_y;
	float			wall_hit_x;
	float			distance;
	int				was_hit_vrtcl;
	int				is_ray_facing_up;
	int				is_ray_facing_down;
	int				is_ray_facing_left;
	int				is_ray_facing_right;
	int				found_horz_wall_hit;
	int				found_vert_wall_hit;
	int				horz_wall_content;
	int				vert_wall_content;
	int				wall_hit_content;
	float			next_horz_touch_x;
	float			next_horz_touch_y;
	float			next_vert_touch_x;
	float			next_vert_touch_y;
	float			horz_wall_hit_x;
	float			horz_wall_hit_y;
	float			vert_wall_hit_x;
	float			vert_wall_hit_y;
	float			horz_hit_distance;
	float			vert_hit_distance;
	float			xintercept;
	float			yintercept;
	float			xstep;
	float			ystep;
	float			x_to_check;
	float			y_to_check;
}					t_ray;

typedef struct s_texture
{
	upng_t			*upngTexture;
	int				width;
	int				height;
	uint32_t		*texture_buffer;
}					t_texture;

typedef struct s_cntnr
{
	SDL_Renderer	*renderer;
	SDL_Window		*window;
	SDL_Texture		*color_bffr_txtre;
	t_texture		wall_textures[3];
	char			*texture_fl_names[TEXTURE_NBR];
	SDL_Rect		map_tile_rect;
	uint32_t		*color_buffer;
	uint32_t		*textures[NUM_TEXTURES];
	int				is_game_running;
	int				ticks_last_frame;
	int				tile_x;
	int				tile_y;
	int				tile_color;
	float			perpDistance;
	float			projectedWallHeight;
	int				wallStripHeight;
	int				wallTopPixel;
	int				wallBottomPixel;
	int				distanceFromTop;
	int				textureOffsetY;
	int				textureOffsetX;
	uint32_t		texelColor;
}					t_cntnr;

void			validate_bites_before_reading(char *argv);
void			read_and_pars_file(t_player *plr, char *argv);
int				check_num_of_cols(t_player *plr);
void			check_num_of_rows(int y);
void			check_contain_of_map(t_player *plr);
void			translate_map_from_char_to_int(t_player *plr);
void			initializing_of_ctnr(t_cntnr *cntnr);
void			setup(t_cntnr *cntnr, t_player *plr);
int				initializing_of_window(t_cntnr *cntnr);
void			process_input(t_cntnr *cntnr, t_player *plr);
void			update(t_cntnr *cntnr, t_player *plr, t_ray *tray);
void			move_player(float deltaTime, t_player *plr);
void			cast_all_rays(t_player *plr, t_ray *tray);
void			castRay(float ray_angle, int stripId,
					t_player *plr, t_ray *trays);
void			render_map(t_cntnr *cntnr, t_player *plr);
int				map_has_wall_at(float x, float y, t_player *plr);
float			distance_between_points(float x1, float y1,
					float x2, float y2);
void			render(t_cntnr *cntnr, t_player *plr, t_ray *trays);
void			generate_3d_projection(t_cntnr *cntnr,
					t_player *plr, t_ray *trays);
void			clear_color_buffer(uint32_t color, t_cntnr *cntnr);
void			render_color_buffer(t_cntnr *cntnr);
void			horizontal_ray_grid_intersection_main(float ray_angle,
					t_player *plr, t_ray *trays);
void			hor_increment_x_y_step_until_a_wall(t_player *plr,
					t_ray *trays);
void			intialization_before_estimates_hor(t_ray *trays);
void			intialization_before_estimates_ver(t_ray *trays);
void			verical_ray_grid_intersection_main(float ray_angle,
					t_player *plr, t_ray *trays);
void			vert_increment_x_y_step_until_a_wall(t_player *plr,
					t_ray *trays);
void			find_the_closer_distance_of_hit_vert_or_hor(int stripId,
					t_player *plr, t_ray *trays);
void			get_correct_texture_id_depend_of_wall_dir(int ray_nbr,
					t_cntnr *cntnr, t_ray *trays);
float			normalize_angle(float angle);
void			initialization_for_cast_ray(float ray_angle, t_ray *trays);
void			cast_ray(float ray_angle, int stripId, t_player *plr,
					t_ray *trays);
SDL_Surface		*img_load(char *path);
void			define_textures(t_cntnr *cntnr);
void			load_wall_textures(t_cntnr *cntnr);
void			free_wall_textures(t_cntnr *cntnr);

#endif