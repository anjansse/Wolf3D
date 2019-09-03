#include "wolf.h"

int		key_fct(int key, void *param, int release)
{
	(void)key;
	(void)param;
	(void)release;
	return (SUCCESS);
}

int		key_left_right(int key, void *param, int release)
{
	double		speed;
	double		player_pl_x;
	double		player_dir_x;
	t_game		*game;

	(void)release;
	game = (t_game *)param;
	player_pl_x = PLAYER_PL.x;
	player_dir_x = PLAYER_DIR.x;
	speed = (key == KEY_LEFT) ? ROTATION_SPEED : -ROTATION_SPEED;
	PLAYER_PL.x = PLAYER_PL.x * cos(speed) - PLAYER_PL.y * sin(speed);
	PLAYER_PL.y = player_pl_x * sin(speed) + PLAYER_PL.y * cos(speed);
	PLAYER_DIR.x = PLAYER_DIR.x * cos(speed) - PLAYER_DIR.y * sin(speed);
	PLAYER_DIR.y = player_dir_x * sin(speed) + PLAYER_DIR.y * cos(speed);
	((t_game *)param)->draw = 1;
	return (SUCCESS);
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
	return (SUCCESS);
}

int		key_fct_esc(int key, void *param, int release)
{
	t_game	*game;

	(void)key;
	(void)release;
	game = (t_game *)param;
	free_map(game->map, (size_t)game->y_max);
	mlx_destroy_image(game->mlx, game->image);
	mlx_clear_window(game->mlx, game->window);
	mlx_destroy_window(game->mlx, game->window);
	exit(EXIT_SUCCESS);
	return (SUCCESS);
}

int		key_press(int key, void *param)
{
	unsigned int			i;
	static t_key_dispatch	key_d[] = {
		{KEY_ESC, &key_fct_esc},
		{KEY_W, &key_fct},
		{KEY_S, &key_fct},
		{KEY_A, &key_fct},
		{KEY_D, &key_fct},
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
	return (SUCCESS);
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
	return (SUCCESS);
}

/* EOF */

