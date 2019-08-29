#include "wolf.h"

int		key_fct(void *param)
{
	(void)param;
	return (0);
}

int		key_left(void *param)
{
	t_game *game;

	game = ((t_game *)param);
	game->bob.theta = ((game->bob.theta + 1) > 359) ? (game->bob.theta + 1) - 360 : game->bob.theta + 1;
	return 1;
}

int		key_right(void *param)
{
	t_game *game;

	game = ((t_game *)param);
	game->bob.theta = ((game->bob.theta - 1) < 0) ? (game->bob.theta - 1) + 360 : game->bob.theta - 1;
	return (1);
}

int		key_fct_esc(void *param)
{
	mlx_destroy_image(((t_game *)param)->mlx, ((t_game *)param)->image);
	mlx_clear_window(((t_game *)param)->mlx, ((t_game *)param)->window);
	mlx_destroy_window(((t_game *)param)->mlx, ((t_game *)param)->window);
	exit(EXIT_SUCCESS);
}

t_key_dispatch	g_key[] = {
	{KEY_ESC, "ESC", &key_fct_esc},
	{KEY_UP, "UP", &key_fct},
	{KEY_DOWN, "DOWN", &key_fct},
	{KEY_LEFT, "LEFT", &key_left},
	{KEY_RIGHT, "RIGHT", &key_right},
	{KEY_SPACE, "SPACE", &key_fct},
	{KEY_SHIFT, "SHIFT", &key_fct},
	{KEY_CMD, "CMD", &key_fct},
	{KEY_CTRL, "CTRL", &key_fct},
	{KEY_ALT, "ALT", &key_fct}
};

int		key_handle(int key, void *param)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_key) / sizeof(t_key_dispatch))
	{
		if (key == g_key[i].key)
			return (g_key[i].fct(param));
		++i;
	}
	return (0);
}

/* EOF */

