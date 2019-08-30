#include "wolf.h"

int		key_fct(int key, void *param, int release)
{
	(void)key;
	(void)param;
	(void)release;
	return (0);
}

int		key_left_right(int key, void *param, int release)
{
	(void)key;
	(void)release;
	t_game *game;

	game = ((t_game *)param);
	game->should_draw = 1;
	if (key == KEY_RIGHT)
		game->bob.theta = ((game->bob.theta + 10) > 359) ? (game->bob.theta + 10) - 360 : game->bob.theta + 10;
	else if (key == KEY_LEFT)
		game->bob.theta = ((game->bob.theta - 10) < 0) ? (game->bob.theta - 10) + 360 : game->bob.theta - 10;
	return 1;
}

// int		key_left(int key, void *param, int release)
// {
// 	(void)key;
// 	(void)release;
// 	t_game *game;

// 	game = ((t_game *)param);
// 	game->should_draw = 1;
// 	game->bob.theta = ((game->bob.theta - 10) < 0) ? (game->bob.theta - 10) + 360 : game->bob.theta - 10;
// 	return (1);
// }

int		key_fct_arrow(int key, void *param, int release)
{
	t_game		*game;
	t_player	*player;

	(void)release;
	game = (t_game *)param;
	player = &(game->bob);
	if (key == KEY_W)
		point_move(game, &(player->position), 1.0, 0.0);
	else if (key == KEY_S)
		point_move(game, &(player->position), -1.0, 0.0);
	else if (key == KEY_D)
		point_move(game, &(player->position), 0.0, 1.0);
	else if (key == KEY_A)
		point_move(game, &(player->position), 0.0, -1.0);
game->should_draw = 1;
	return (0);
}

int		key_fct_shift(int key, void *param, int release)
{
	t_game	*game;

	(void)key;
	game = (t_game *)param;
	if (release)
		game->bob.speed = PLAYER_SPEED_REG;
	else
		game->bob.speed = PLAYER_SPEED_RUN;
	return (0);
}

int		key_fct_esc(int key, void *param, int release)
{
	t_game	*game;

	(void)key;
	(void)release;
	game = (t_game *)param;
	free_map(game->map, (size_t)game->x_max);
	mlx_destroy_image(game->mlx, game->image);
	mlx_clear_window(game->mlx, game->window);
	mlx_destroy_window(game->mlx, game->window);
	exit(EXIT_SUCCESS);
	return (0);
}

int		key_press(int key, void *param)
{
	unsigned int			i;
	static t_key_dispatch	key_d[] = {
		{KEY_ESC, &key_fct_esc},
		{KEY_W, &key_fct_arrow},
		{KEY_S, &key_fct_arrow},
		{KEY_A, &key_fct_arrow},
		{KEY_D, &key_fct_arrow},
		{KEY_SHIFT, &key_fct_shift},
		{KEY_RIGHT, &key_left_right},
		{KEY_LEFT, &key_left_right},
	};

	i = 0;
	while (i < sizeof(key_d) / sizeof(t_key_dispatch))
	{
		if (key == key_d[i].key)
			return (key_d[i].fct(key, param, 0));
		++i;
	}
	return (0);
}

int		key_release(int key, void *param)
{
	unsigned int			i;
	static t_key_dispatch	key_d[] = {
		{KEY_SHIFT, &key_fct_shift}
	};

	i = 0;
	while (i < sizeof(key_d) / sizeof(t_key_dispatch))
	{
		if (key == key_d[i].key)
			return (key_d[i].fct(key, param, 1));
		++i;
	}
	return (0);
}

/* EOF */

