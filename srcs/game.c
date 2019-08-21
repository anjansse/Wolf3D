#include "wolf.h"

static const unsigned char  map[MAP_HEIGTH][MAP_WIDTH] = {
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
	{0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01},
	{0x01, 0x00,  'P', 0x00, 0x00, 0x01, 0x00, 0x01},
	{0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01},
	{0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
	{0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01},
	{0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
};

static void		window_background(unsigned int *pixels, size_t size)
{
	size_t 	i;

	i = 0;
	while (i < size)
	{
		pixels[i] = (i < (size / 2)) ? 0xCDE5FC : 0xFFCC99;
		++i;
	}
}

void			game_init(t_game game)
{
	void    		*new_image;
	unsigned char	*img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	
	(void)map;
	
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	new_image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	img = (unsigned char *)mlx_get_data_addr(new_image, &bits_per_pixel, &size_line, &endian);
	window_background((unsigned int *)img, SCREEN_WIDTH * SCREEN_HEIGTH);
	mlx_put_image_to_window(game.mlx, game.window, new_image, 0, 0);
	mlx_key_hook(game.window, key_handle, &game);
	mlx_loop(game.mlx);
}

/* EOF MAX */
