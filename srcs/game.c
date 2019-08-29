#include "wolf.h"

void			player_init(t_player *player, int x, int y, float theta)
{
	player->position.x = x * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->position.y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->theta = theta;
	player->speed = PLAYER_SPEED_REG;
}

void			game_init(t_game game)
{
	double	distance;
	int		pixels;
	int		size_line;
	int		endian;

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	game.pixels = (unsigned int *)mlx_get_data_addr(game.image, &pixels, &size_line, &endian);
	put_background(game, SCREEN_WIDTH * SCREEN_HEIGTH);
	player_init(&(game.bob), 2, 3, 0.0);
	distance = wall_distance(&game, game.bob.theta);
	// __DEBUG__
	printf("%f\n", distance);
	printf("[%d, %d] %d\n", (int)(game.bob.position.x / BLOCK_SIZE), (int)(game.bob.position.y / BLOCK_SIZE), (int)(game.bob.speed));
	// !__DEBUG__
	mlx_put_image_to_window(game.mlx, game.window, game.image, 0, 0);
	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 3, 0, key_release, &game);
	mlx_loop(game.mlx);
}

/* EOF */
