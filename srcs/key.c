#include "wolf.h"

int		key_fct(void *param)
{
	(void)param;
	return (0);
}

int		key_fct_esc(void *param)
{
	mlx_clear_window(((t_game *)param)->mlx, ((t_game *)param)->window);
	mlx_destroy_window(((t_game *)param)->mlx, ((t_game *)param)->window);
	exit(EXIT_SUCCESS);
}

t_key_dispatch	g_key[] = {
	{KEY_ESC, "ESC", &key_fct_esc},
	{KEY_UP, "UP", &key_fct},
	{KEY_DOWN, "DOWN", &key_fct},
	{KEY_LEFT, "LEFT", &key_fct},
	{KEY_RIGHT, "RIGHT", &key_fct},
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
	while (i < sizeof(g_key))
	{
		if (g_key[i].key == key)
		{
			ft_putendl(g_key[i].name);
			return (g_key[i].fct(param));
		}
		++i;
	}
	return (0);
}