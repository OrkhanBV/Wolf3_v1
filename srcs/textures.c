#include <wolf3d.h>
#include <stdio.h>

void	load_wall_textures(t_cntnr *cntnr)
{
	upng_t	*upng;
	int		i;

	i = 0;
	while (i < TEXTURE_NBR)
	{
		upng = upng_new_from_file(cntnr->texture_fl_names[i]);
		if (upng != NULL)
		{
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK)
			{
				cntnr->wall_textures[i].upng_texture = upng;
				cntnr->wall_textures[i].width = upng_get_width(upng);
				cntnr->wall_textures[i].height = upng_get_height(upng);
				cntnr->wall_textures[i].texture_buffer = (
						uint32_t *)upng_get_buffer(upng);
			}
		}
		i++;
	}
}

void	free_wall_textures(t_cntnr *cntnr)
{
	int	i;

	i = 0;
	while (i < TEXTURE_NBR)
	{
		upng_free(cntnr->wall_textures[i].upng_texture);
		i++;
	}
}
