#include <wolf3d.h>
#include <stdio.h>

void	load_wall_textures(t_cntnr *cntnr)
{
	upng_t	*upng;
	int		i;

	i = 0;
	while (i < TEXTURE_NBR)
	{
		upng = upng_new_from_file(cntnr->textureFileNames[i]);
		if (upng != NULL)
		{
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK)
			{
				cntnr->wallTextures[i].upngTexture = upng;
				cntnr->wallTextures[i].width = upng_get_width(upng);
				cntnr->wallTextures[i].height = upng_get_height(upng);
				cntnr->wallTextures[i].texture_buffer = (
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
		upng_free(cntnr->wallTextures[i].upngTexture);
		i++;
	}
}
