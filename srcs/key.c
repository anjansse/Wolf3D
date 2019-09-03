#include "wolf.h"

static int	key_movement(int key, void *param, int release)
{
	uint8_t	*game;

	game = &((t_game *)param)->move;
	if (key == KEY_W)
		*game = (release) ? *game ^ MOVE_FRONT : *game | MOVE_FRONT;
	if (key == KEY_S)
		*game = (release) ? *game ^ MOVE_BACK : *game | MOVE_BACK;
	if (key == KEY_A)
		*game = (release) ? *game ^ MOVE_LEFT : *game | MOVE_LEFT;
	if (key == KEY_D)
		*game = (release) ? *game ^ MOVE_RIGHT : *game | MOVE_RIGHT;
	if (key == KEY_SHIFT)
		((t_game *)param)->bob.speed = (release) ? PLAYER_SPEED_REG : PLAYER_SPEED_RUN;
	return (SUCCESS);
}

static int	key_rotation(int key, void *param, int release)
{
	uint8_t	*game;

	game = &((t_game *)param)->move;
	if (key == KEY_LEFT)
		*game = (release) ? *game ^ ROTATE_LEFT : *game | ROTATE_LEFT;
	if (key == KEY_RIGHT)
		*game = (release) ? *game ^ ROTATE_RIGTH : *game | ROTATE_RIGTH;
	return (SUCCESS);
}

static int	key_fct_esc(int key, void *param, int release)
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

int			key_press(int key, void *param)
{
	unsigned int			i;
	static t_key_dispatch	key_d[] = {
		{KEY_ESC, &key_fct_esc},
		{KEY_W, &key_movement},
		{KEY_S, &key_movement},
		{KEY_A, &key_movement},
		{KEY_D, &key_movement},
		{KEY_LEFT, &key_rotation},
		{KEY_RIGHT, &key_rotation},
		{KEY_SHIFT, &key_movement}
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

int			key_release(int key, void *param)
{
	unsigned int			i;
	static t_key_dispatch	key_d[] = {
		{KEY_W, &key_movement},
		{KEY_S, &key_movement},
		{KEY_A, &key_movement},
		{KEY_D, &key_movement},
		{KEY_LEFT, &key_rotation},
		{KEY_RIGHT, &key_rotation},
		{KEY_SHIFT, &key_movement}
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
