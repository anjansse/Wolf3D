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
	double		rotSpeed;
	double		player_dir;
	double		player_plane;
	t_player	*player;

	(void)release;
	player = &((t_game *)param)->bob;
	player_dir = player->dir.x;
	player_plane = player->plane.x;
	rotSpeed = player->frame * 2.0;
    if (key == KEY_RIGHT)
		rotSpeed = -rotSpeed;
	player->dir.x = player->dir.x * cos(rotSpeed) - player->dir.y * sin(rotSpeed);
	player->dir.y = player_dir * sin(rotSpeed) + player->dir.y * cos(rotSpeed);
	player->plane.x = player->plane.x * cos(rotSpeed) - player->plane.y * sin(rotSpeed);
	player->plane.y = player_plane * sin(rotSpeed) + player->plane.y * cos(rotSpeed);
	((t_game *)param)->draw = 1;
	return 1;
}

int		key_fct_arrow(int key, void *param, int release)
{
	(void)key;
	(void)param;
	(void)release;
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
	free_map(game->map, (size_t)game->y_max);
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

