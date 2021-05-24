#include <wolf3d.h>

void	validate_bites_before_reading(char *argv)
{
	int		bytes;
	char	simbol;
	int		fd;

	fd = open(argv, O_RDONLY);
	bytes = read(fd, &simbol, 1);
	if (bytes < 0)
	{
		ft_putstr("Error\n");
		exit(1);
	}
	close(fd);
}

int	check_num_of_cols(t_player *plr)
{
	if (ft_strlen(plr->crude_map[1]) != (MAP_NUM_COLS))
		return (1);
	if (ft_strlen(plr->crude_map[1]) == (MAP_NUM_COLS))
		return (0);
	return (1);
}

void	check_num_of_rows(int y)
{
	if (y != MAP_NUM_ROWS)
	{
		ft_putstr("ERROR : Not valid number of rows\n");
		exit(0);
	}
}

void	print_error(char *str)
{
	ft_putstr(str);
	exit(0);
}

void	check_contain_of_map(t_player *plr)
{
	int	i;
	int	j;

	j = 0;
	while (j < MAP_NUM_ROWS)
	{
		i = 0;
		while (i < MAP_NUM_COLS)
		{
			if (plr->crude_map[MAP_NUM_ROWS - 1][i] != '1' ||
				plr->crude_map[0][i] != '1')
				print_error("ERROR : Not valid map\n");
			if (plr->crude_map[j][MAP_NUM_COLS - 1] != '1' ||
				plr->crude_map[j][0] != '1' || plr->crude_map[6][9] == '1')
				print_error("ERROR : Not valid map\n");
			if (plr->crude_map[j][i] == '0' || plr->crude_map[j][i] == '1')
				i++;
			else
				print_error("ERROR : Not valid map\n");
		}
		j++;
	}
}
