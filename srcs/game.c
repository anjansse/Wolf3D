#include "wolf.h"

/*
** Find the last point of the map
*/

static uint8_t	wall_hit(t_game *game, t_point *map, t_vector *side, t_vector *delta)
{
	uint8_t		hit;
	uint8_t		range;

	hit = 0;
	while (hit == 0)
	{
		range = (side->x < side->y) ? 0 : 1;
		if (side->x < side->y)
		{
			side->x += delta->x;
			map->x += game->step.x;
		}
		else
		{
			side->y += delta->y;
			map->y += game->step.y;
		}
		if (0 > map->x || map->x >= game->x_max
			|| 0 > map->y || map->y >= game->y_max)
			return (2);
		if (game->map[(int)floor(map->y)][(int)floor(map->x)] != 0)
			hit = 1;
	}
	return (range);
}

/*
** DDA, find distances of walls if they exists and return it.
*/

static uint8_t	dda(t_game *game, t_vector *ray, t_point *map, double x)
{
	double		angle;
	uint8_t		range;
	t_vector	side;
	t_vector	delta;

	angle = 2 * x / SCREEN_WIDTH - 1;
	vector_update(ray, PLAYER_PL.x * angle, PLAYER_PL.y * angle);
	vector_set(&delta, (ray->x == 0.0) ? 1.0 : fabs(1 / ray->x), 0.0);
	vector_set(&delta, delta.x, (ray->y == 0.0) ? 1.0 : fabs(1 / ray->y));
	game->step.x = (ray->x < 0.0) ? -1 : 1;
	game->step.y = (ray->y < 0.0) ? -1 : 1;
	if (ray->x < 0.0)
		side.x = (PLAYER_POS.x - map->x) * delta.x;
	else
		side.x = (map->x + 1.0 - PLAYER_POS.x) * delta.x;
	if (ray->y < 0.0)
		side.y = (PLAYER_POS.y - map->y) * delta.y;
	else
		side.y = (map->y + 1.0 - PLAYER_POS.y) * delta.y;
	range = wall_hit(game, map, &side, &delta);
	return (range);
}

/*
** Gets distance for walls and display them.
** Does this for total width of opened window.
*/

static void		display_walls(t_game *game)
{
	double		distance;
	uint8_t		range;
	t_point		map;
	t_point		point;
	t_vector	ray;

	point_set(&point, 0, 0);
	while (point.x < SCREEN_WIDTH)
	{
		point_set(&map, PLAYER_POS.x, PLAYER_POS.y);
		vector_set(&ray, PLAYER_DIR.x, PLAYER_DIR.y);
		range = dda(game, &ray, &map, point.x);
		if (range == 0 && ray.x != 0.0)
			distance = (map.x - PLAYER_POS.x + (1.0 - game->step.x) / 2.0) / ray.x;
		else if (range == 1 && ray.y != 0.0)
			distance = (map.y - PLAYER_POS.y + (1.0 - game->step.y) / 2.0) / ray.y;
		else if (range == 2)
			distance = SCREEN_HEIGTH;
		distance = (distance <= 1.0) ? 1.0 : (distance >= SCREEN_HEIGTH) ? SCREEN_HEIGTH - 1 : distance;
		put_column(game, point, (int)(SCREEN_HEIGTH / distance), (range == 1) ? 0x00FBFF : 0xFF00FF);
		++point.x;
	}
}

/*
** Main function called in loop_hook. Used to print every element on the map
** (Walls, your imagination, that's it, ....)
*/

int				display_map(t_game *game)
{
	player_rotation(game);
	player_movement(game);
	put_background(game, PP_DIMENSION);
	display_walls(game);
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	return (SUCCESS);
}

/*
** Main Game function, initializes the window, prints background and walls
** contained into player's current fov, and get's user inputted keys.
*/

void			game_init(t_game game)
{
	int		t;
	int		pixels;
	int		size_line;
	int		endian;

	game.mlx = mlx_init();
	game.textures = (uint32_t **)malloc(sizeof(uint32_t *) * 2);
	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	game.txt = mlx_xpm_file_to_image(game.mlx, "./texture/wall_txt/stone_wall.xpm", &t, &t);
	game.pixels = (uint32_t *)mlx_get_data_addr(game.image, &pixels, &size_line, &endian);
	game.textures[0] = (uint32_t *)mlx_get_data_addr(game.txt, &pixels, &size_line, &endian);
	player_set(&(game.bob), 3, 3);
	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 3, 0, key_release, &game);
	mlx_loop_hook(game.mlx, display_map, &game);
	mlx_loop(game.mlx);
}

/* EOF */
