#include "wolf.h"

void			player_init(t_player *player, int x, int y, float theta)
{
	player->position.x = x * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->position.y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->theta = theta;
	player->speed = PLAYER_SPEED_REG;
}

/*
** Displays the walls contained in the player's fov.
** Takes the distance between each ray casted and a wall/border of the map
** and handles it appropriately.
*/


static void		display_walls(t_game *game)
{
	t_vector	point;	
	double 		fov_angle;
	double		fov_min;
	double		fov_max;
	double 		distance;

	point.x = 0.0;
	point.y = 0.0;
	fov_min = 0.0;
	fov_max = 60.0;
	fov_angle = (game->bob.theta - 30 >= 0) ? (game->bob.theta - 30) : (game->bob.theta - 30) + 360;
	printf("theta: %f\tfov_angle: %f\tfov_max: %f\n", game->bob.theta, fov_angle, fov_max);
	while (fov_min < fov_max)
	{
		distance = wall_distance(game, fov_angle);
		// printf("\x1b[91mdistance:\t%f\x1b[0m\n", distance);
		put_column(game, point, (64.0 / distance) * PP_DISTANCE, 0xFF0C00);
		fov_angle = (fov_angle + (double)PP_UNIT > 360) ? (fov_angle + (double)PP_UNIT) - 360 : fov_angle + (double)PP_UNIT;
		fov_min += (double)PP_UNIT;
		point.x++;
		// printf("\x1b[91mPP_UNIT: %f\tfov_angle: %f\tdistance: %f\tx: %f\x1b[0m\n", (double)PP_UNIT, fov_angle, distance, point.x);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
}

/*
** Main function called in loop_hook. Used to print every element on the map
** (Walls, your imagination, that's it, ....)
*/

int				display_map(t_game *game)
{
	display_walls(game);
	return (1);
}

/*
** Main Game function, initializes the window, prints background and walls
** contained into player's current fov, and get's user inputted keys.
*/

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
	mlx_put_image_to_window(game.mlx, game.window, game.image, 0, 0);
	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 3, 0, key_release, &game);
	mlx_loop_hook(game.mlx, display_map, &game);
	mlx_loop(game.mlx);
}

/* EOF */
