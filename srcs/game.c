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
	PLAYER.theta = 22.0;
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
	double		fov_max;
	double 		distance;

	point.x = 0;
	point.y = 0;
	fov_angle = (game->bob.theta - 30 > 0) ? (game->bob.theta - 30) + 360 : game->bob.theta - 30;
	fov_max = (game->bob.theta - 30 > 0) ? (game->bob.theta - 30) + 360 : game->bob.theta - 30;
	while (fov_angle < fov_max)
	{
		distance = distance_wall(game, fov_angle);
		put_column(game, point, (64.0 / distance) * PP_DISTANCE, 0xFF0C00);
		fov_angle += PP_UNIT;
		point.x++;
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
	double		distance;
	int		pixels;
	int		size_line;
	int		endian;

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	game.pixels = (unsigned int *)mlx_get_data_addr(game.image, &pixels, &size_line, &endian);
	put_background(game, SCREEN_WIDTH * SCREEN_HEIGTH);
	fov_handle(&game);
	distance = distance_wall(&game, game.bob.theta);
	mlx_put_image_to_window(game.mlx, game.window, game.image, 0, 0);
	mlx_key_hook(game.window, key_handle, &game);
	mlx_loop_hook(game.mlx, display_map, &game);
	mlx_loop(game.mlx);
}

/* EOF */
