#include "wolf.h"

void			player_init(t_player *player, int x, int y)
{
	ft_memset(player, 0, sizeof(t_player));
	player->pos.x = x;
	player->pos.y = y;
	player->dir.x = -1;
	player->plane.y = 0.60;
	player->speed = PLAYER_SPEED_REG;
}

void		vector_set(t_vector *point, double x, double y)
{
	point->x = x;
	point->y = y;
}

void		point_set(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

static void		player_time(t_player *player, struct timeval t)
{
	double			frame;
	struct timeval	old;

	ft_memcpy(&old, &t, sizeof(struct timeval));
	gettimeofday(&t, 0);
	frame = (t.tv_sec - old.tv_sec) * 1000.0f + (t.tv_usec - old.tv_usec) / 1000.0f;
	player->frame = frame / 1000.0;
}

static t_uchar	dda(t_game *game, t_vector *ray, t_point *map, t_point *step, double x)
{
	t_uchar		hit;
	t_uchar		sideMap;
	double		camera;
	t_vector	side;
	t_vector	delta;

	camera = 2 * x / SCREEN_WIDTH - 1;
	point_set(map, (int)game->bob.pos.x, (int)game->bob.pos.y);
	vector_set(ray, game->bob.dir.x + game->bob.plane.x * camera, game->bob.dir.y + game->bob.plane.y * camera);
	vector_set(&delta, fabs(1 / ray->x), fabs(1 / ray->y));
	step->x = (ray->x < 0) ? -1 : 1;
	if (ray->x < 0)
		side.x = (game->bob.pos.x - map->x) * delta.x;
	else
		side.x = (map->x + 1.0 - game->bob.pos.x) * delta.x;
	step->y = (ray->y < 0) ? -1 : 1;
	if (ray->y < 0)
		side.y = (game->bob.pos.y - map->y) * delta.y;
	else
		side.y = (map->y + 1.0 - game->bob.pos.y) * delta.y;
	hit = 0;
	while (hit == 0)
	{
		sideMap = (side.x < side.y) ? 0 : 1;
		if (side.x < side.y)
		{
			side.x += delta.x;
			map->x += step->x;
		}
		else
		{
			side.y += delta.y;
			map->y += step->y;
		}
		if (0 <= map->x && map->x < game->x_max && 0 <= map->y && map->y < game->y_max)
		{
			if (game->map[map->y][map->x] != 0)
				hit = 1;
		}
		else
			hit = 1;
	}
	return (sideMap);
}

static void		display_walls(t_game *game)
{
	double		wallDistance;
	t_vector	ray;
	t_player	*player;
	t_point		map;
	t_point		step;
	t_uchar		sideMap;
	int			lineHeigth;

	t_point		point;

	player = &(game->bob);
	point_set(&point, 0, 0);
	while (point.x < SCREEN_WIDTH)
	{
		sideMap = dda(game, &ray, &map, &step, point.x);
		if (sideMap == 0)
			wallDistance = (map.x - player->pos.x + (1 - step.x) / 2) / ray.x;
		else
			wallDistance = (map.y - player->pos.y + (1 - step.y) / 2) / ray.y;
		lineHeigth = (int)(SCREEN_HEIGTH / wallDistance);
		put_column(game, point, lineHeigth, 0x00FBFF);
		++point.x;
	}
}

/*
** Main function called in loop_hook. Used to print every element on the map
** (Walls, your imagination, that's it, ....)
*/

int				display_map(t_game *game)
{
	struct timeval	time;

	ft_memset(&time, 0, sizeof(struct timeval));
	if (game->draw == 1)
	{
		put_background(game, PP_DIMENSION);
		gettimeofday(&time, 0);
		display_walls(game);
		player_time(&(game->bob), time);
		mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	}
	game->draw = 0;
	return (1);
}

/*
** Main Game function, initializes the window, prints background and walls
** contained into player's current fov, and get's user inputted keys.
*/

void			game_init(t_game game)
{
	int		pixels;
	int		size_line;
	int		endian;

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	game.pixels = (unsigned int *)mlx_get_data_addr(game.image, &pixels, &size_line, &endian);
	game.draw = 1;
	player_init(&(game.bob), 3, 3);
	mlx_hook(game.window, 2, 0, key_press, &game);
	// mlx_hook(game.window, 3, 0, key_release, &game);
	mlx_loop_hook(game.mlx, display_map, &game);
	mlx_loop(game.mlx);
}

/* EOF */
