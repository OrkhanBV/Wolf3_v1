# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jremarqu <jremarqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/01 22:38:24 by jremarqu          #+#    #+#              #
#    Updated: 2021/05/24 21:08:21 by jremarqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Wolf3d

INC_DIR		= ./includes
INC_DIR_T	= ./Frameworks_SDL/Texteure_loading/Header
SRC_DIR		= ./srcs
OBJ_DIR		= ./objects

HEADERS		= wolf3d.h

SOURCES_C	= 	main.c 									\
				part_0_0_parser.c						\
				part_0_1_validation.c					\
				part_1_initialization_and_setup.c		\
				part_2_process_input.c					\
				part_3_0_horizont_intersection.c		\
				part_3_1_vertical_intersection.c		\
				part_3_2_closer_distance_vert_or_hor.c	\
				part_3_3_casting_of_ray.c				\
				part_4_update.c							\
				part_5_0_helper_get_texture.c			\
				part_5_1_the_3d_projection.c			\
				part_5_2_render_and_clear_color_buf.c	\
				part_5_3_render.c						\
				textures.c								\
														\

LIBFT_DIR			=	./includes/libft
LIB_LOAD_TEXTURE	= ./Frameworks_SDL/Texteure_loading
LIBFT				= $(LIBFT_DIR)/libft.a

CC = gcc
WFLAGS		= -Wall -Wextra -Werror -g

IFLAGS	= 																\
		-I./includes/													\
		-I Frameworks_SDL/SDL2.framework/Versions/A/Headers				\
		-I Frameworks_SDL/SDL2_ttf.framework/Versions/A/Headers			\
		-I Frameworks_SDL/SDL2_image.framework/Versions/A/Headers		\
		-I Frameworks_SDL/SDL2_mixer.framework/Headers					\
		-I Frameworks_SDL/SDL2.framework/Versions/A/Headers				\
		-I Frameworks_SDL/SDL2/SDL2_image.framework/Versions/A/Header	\
		-I Frameworks_SDL/SDL2/SDL2_ttf.framework/Versions/A/Header		\
		-I Frameworks_SDL/SDL2/SDL2_mixer.framework/Versions/A/Header	\
		-I$(INC_DIR_T)													\
		-I$(INC_DIR)/ -I$(LIBFT_DIR)/includes/							\
		-F Frameworks_SDL/												\

LFLAGS		= -L$(LIB_LOAD_TEXTURE) -lft -lupng							\
			-L$(LIBFT_DIR)/ -lft										\


MLX_FLAGS	= -I minilibx -lmlx -framework OpenGL -framework AppKit

INCS	= $(addprefix $(INC_DIR)/, $(HEADERS))
SRCS_C	= $(addprefix $(SRC_DIR)/, $(SOURCES_C))
OBJS_C	= $(addprefix $(OBJ_DIR)/, $(SOURCES_C:.c=.o))
FRAME	= -F Frameworks_SDL/ -framework SDL2 -framework SDL2_image		\
		-framework SDL2_ttf -framework SDL2_mixer -rpath Frameworks_SDL/

all: 
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) $(NAME)

$(NAME): $(OBJS_C)
	$(CC) $(WFLAGS) $(IFLAGS) $(OBJS_C) $(LFLAGS) $(MLX_FLAGS) $(FRAME) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) Makefile
	@mkdir -p ${@D}
	$(CC) $(WFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME).dSYM

fclean: clean
	rm -rf $(NAME)


re: fclean all

run: all
	./Wolf3d /Users/jremarqu/Desktop/Wolf3d_start/srcs/map.txt

norm:
	@norminette $(INCS) $(SRCS_C)

.PHONY: all clean fclean re norm vv
