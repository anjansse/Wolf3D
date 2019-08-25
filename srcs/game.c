#include "wolf.h"

/*
static const unsigned char  map[MAP_HEIGTH][MAP_WIDTH] = {
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
	{0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01},
	{0x01, 0x00,  'P', 0x00, 0x00, 0x01, 0x00, 0x01},
	{0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01},
	{0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
	{0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01},
	{0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
};
*/

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
	PLAYER.position.x = 2; // add 'P' x position when parser done.
	PLAYER.position.y = 2; // add 'P' y position when parser done.0
	PLAYER.direction = 0.0;
	fov_render(game);
}

void			game_init(t_game game)
{
	int		pixels;
	int		size_line;
	int		endian;

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	game.pixels = (unsigned int *)mlx_get_data_addr(game.image, &pixels, &size_line, &endian);
	put_background(game, SCREEN_WIDTH * SCREEN_HEIGTH);
	fov_handle(&game);
	mlx_put_image_to_window(game.mlx, game.window, game.image, 0, 0);
	mlx_key_hook(game.window, key_handle, &game);
	mlx_loop(game.mlx);
}

/* EOF */
