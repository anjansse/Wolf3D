#include "wolf.h"

void		get_texture(t_game *game)
{
	int		t;
	int		pixels;
	int		size_line;
	int		endian;

	game->txt = mlx_xpm_file_to_image(game->mlx, "./texture/wall_txt/stone_wall.xpm", &t, &t);
	game->textures[0] = (uint32_t *)mlx_get_data_addr(game->txt, &pixels, &size_line, &endian);
	game->txt = mlx_xpm_file_to_image(game->mlx, "./texture/wall_txt/stone_wall_d.xpm", &t, &t);
	game->textures[1] = (uint32_t *)mlx_get_data_addr(game->txt, &pixels, &size_line, &endian);
	game->txt = mlx_xpm_file_to_image(game->mlx, "./texture/floor_txt/marbre.xpm", &t, &t);
	game->textures[2] = (uint32_t *)mlx_get_data_addr(game->txt, &pixels, &size_line, &endian);
}

void		point_set(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

void		vector_set(t_vector *point, double x, double y)
{
	point->x = x;
	point->y = y;
}

void		vector_update(t_vector *point, double x, double y)
{
	point->x += x;
	point->y += y;
}

/* EOF */
