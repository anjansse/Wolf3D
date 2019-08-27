#include "wolf.h"

void			fov_render(t_game *game)
{
	double min;
	double max;

	(void)game;
	min = (double)FOV / 2;
	max = 360.0 - (double)FOV / 2;
}

void			fov_handle(t_game *game)
{
	PLAYER.position.x = 2 * BLOCK_SIZE + BLOCK_SIZE/2;
	PLAYER.position.y = 3 * BLOCK_SIZE + BLOCK_SIZE/2;
	PLAYER.theta = 180.0;
}

void			game_init(t_game game)
{
	double		distance;
	// int		pixels;
	// int		size_line;
	// int		endian;

	// game.mlx = mlx_init();
	// game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	// game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	// game.pixels = (unsigned int *)mlx_get_data_addr(game.image, &pixels, &size_line, &endian);
	// put_background(game, SCREEN_WIDTH * SCREEN_HEIGTH);
	fov_handle(&game);
	distance = distance_wall(&game, game.bob.theta);
	// mlx_put_image_to_window(game.mlx, game.window, game.image, 0, 0);
	// mlx_key_hook(game.window, key_handle, &game);
	// mlx_loop(game.mlx);
}

/* EOF */
