#include "wolf.h"

int		main(int argc, char *argv[])
{
	t_game		game;

	(void)argc;
	(void)argv;
	ft_memset(&game, 0, sizeof(t_game));
	game_init(game);
	return (0);
}

/* EOF */
