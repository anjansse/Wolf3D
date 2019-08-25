#include "wolf.h"

void			send_error(char *str)
{
	ft_putstr(str);
	exit(1);
}

int				main(int ac, char **av)
{
	t_game		game;

	if (ac != 2)
		send_error("usage: ./wolf3d <map>\n");
	ft_memset(&game, 0, sizeof(t_game));
	file_parse(av[1], &game);
	// game_init(game);
	return (0);
}

/* EOF */
