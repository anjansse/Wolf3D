#include "wolf.h"

void        game_init(t_game game)
{
    game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 800, 450, "Wolf3D");
	mlx_key_hook(game.window, key_handle, &game);
	mlx_loop(game.mlx);
}

/* EOF MAX */
