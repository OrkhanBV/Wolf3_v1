#include <wolf3d.h>

void	read_and_pars_file(t_player *plr, char *argv)
{
	char		*line;
	int			fd;
	int			y;
	int			i;

	fd = open(argv, O_RDONLY);
	y = 0;
	validate_bites_before_reading(argv);
	while (get_next_line(fd, &line) != 0)
	{
		i = 0;
		while ((line[i] != '\0' || line[i] != '\n') && i <= MAP_NUM_COLS)
		{
			plr->crude_map[y][i] = line[i];
			i++;
		}
		plr->crude_map[y][i] = '\0';
		y++;
		free(line);
	}
	check_num_of_rows(y);
	free(line);
}

int	ft_simbol_atoi(const char c)
{
	size_t	i;
	size_t	res;
	size_t	sum;

	i = 0;
	res = 1;
	sum = 0;
	if ((c >= '0') && (c <= '9'))
		sum = (sum * 10 + (c - '0'));
	return ((int)(res * sum));
}

void	translate_map_from_char_to_int(t_player *plr)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_NUM_ROWS)
	{
		x = 0;
		while (x < MAP_NUM_COLS)
		{
			plr->map[y][x] = ft_simbol_atoi((plr->crude_map[y][x]));
			x++;
		}
		y++;
	}
}
