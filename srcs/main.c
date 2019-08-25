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
	if (EXIT_FAILURE == parser(av[1], &game))
		return (1);
	free_map(game.map, (size_t)game.x_max);
	// game_init(game);
	return (0);
}

/* EOF */
