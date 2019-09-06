#include "wolf.h"

/*
** Find either a wall, or returns no wall (empty map).
*/

static uint8_t wall_hit(t_game *game, t_point *map, t_vector *side, t_vector *delta)
{
	uint8_t hit;
	uint8_t range;

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
		if (0 > map->x || map->x >= game->x_max || 0 > map->y || map->y >= game->y_max)
			return (2);
		if (game->map[(int)floor(map->y)][(int)floor(map->x)] != 0)
			hit = 1;
	}
	return (range);
}

/*
** DDA, find distances of walls if they exists and return it.
*/

static uint8_t dda(t_game *game, t_vector *ray, t_point *map, double x)
{
	double angle;
	uint8_t range;
	t_vector side;
	t_vector delta;

	angle = 2.0 * x / SCREEN_WIDTH - 1;
	vector_update(ray, PLAYER_PL.x * angle, PLAYER_PL.y * angle);
	vector_set(&delta, (ray->x == 0.0) ? 1.0 : fabs(1.0 / ray->x), 0.0);
	vector_set(&delta, delta.x, (ray->y == 0.0) ? 1.0 : fabs(1.0 / ray->y));
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
	// printf("delta.x = %f\n", delta.x);
	// printf("delta.y = %f\n\nm", delta.y);
	range = wall_hit(game, map, &side, &delta);
	return (range);
}

/*
** Gets distance for walls and display them.
** Does this for total width of opened window.
*/

static void display_walls(t_game *game)
{
	double distance;
	uint8_t range;
	t_point map;
	t_point point;
	t_vector ray;

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
		put_column(game, point, (int)(SCREEN_HEIGTH / distance), (range == 1) ? 0xBBBBC2 : 0x94949B);
		// int texX;
		// double	WallX;
		// uint32_t	buffer[SCREEN_HEIGTH][SCREEN_WIDTH];

		// WallX = (range == 0) ? PLAYER_POS.y + distance + ray.y : PLAYER_POS.x + distance + ray.x;
		// WallX -= floor(WallX);
		// texX = (int)(WallX * 64.0);
		// texX = 64 - texX - 1;
		// int drawStart = -distance / 2 + SCREEN_HEIGTH / 2;
  	    // if(drawStart < 0) drawStart = 0;
  	    // int drawEnd = distance / 2 + SCREEN_HEIGTH / 2;
  	    // if(drawEnd >= SCREEN_HEIGTH) drawEnd = SCREEN_HEIGTH - 1;
		// for (int y = drawStart; y < drawEnd; y++)
  	    // {
	    //   for(int x = drawStart; x <drawEnd; x++)
		//   {
  	    //   int d = y * 256 - SCREEN_HEIGTH * 128 + distance * 128;  //256 and 128 factors to avoid floats
  	    //   // TODO: avoid the division to speed this up
  	    //   int texY = ((d * 64) / distance) / 256;
		// 	printf("result: %d\n", 64 * texY + texX);
  	    //   uint32_t color = game->textures[(range == 1) ? 0 : 1][64 * texY + texX];
  	    //   //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		//   if(range == 1) color = (color >> 1) & 8355711;
  	    //   buffer[y][x] = color;
    	//   }
    	// }
		// put_column(game, point, (int)(SCREEN_HEIGTH / distance), color);
		// game->pixels[point.y * SCREEN_WIDTH + point.x] = buffer[0][0];
		++point.x;
	}
}

/*
** Main function called in loop_hook. Used to print every element on the map
** (Walls, your imagination, that's it, ....)
*/

int display_map(t_game *game)
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

void game_init(t_game game)
{
	int pixels;
	int size_line;
	int endian;

	game.mlx = mlx_init();
	game.textures = (uint32_t **)malloc(sizeof(uint32_t *) * 8);
	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	game.pixels = (uint32_t *)mlx_get_data_addr(game.image, &pixels, &size_line, &endian);
	// get_texture(&game);
	game.textures[0] = malloc(sizeof(uint32_t) * 4096); 
	game.textures[1] = malloc(sizeof(uint32_t) * 4096); 
	game.textures[2] = malloc(sizeof(uint32_t) * 4096); 
	game.textures[3] = malloc(sizeof(uint32_t) * 4096); 
	game.textures[4] = malloc(sizeof(uint32_t) * 4096); 
	game.textures[5] = malloc(sizeof(uint32_t) * 4096); 
	game.textures[6] = malloc(sizeof(uint32_t) * 4096); 
	game.textures[7] = malloc(sizeof(uint32_t) * 4096); 
	for (int x = 0; x < 64; x++)
		for (int y = 0; y < 64; y++)
		{
			int xorcolor = (x * 256 / 64) ^ (y * 256 / 64);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / 64;
			int xycolor = y * 128 / 64 + x * 128 / 64;
			game.textures[0][64 * y + x] = 65536 * 254 * (x != y && x != 64 - y);  //flat red texture with black cross
			game.textures[1][64 * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;	//sloped greyscale
			game.textures[2][64 * y + x] = 256 * xycolor + 65536 * xycolor;				 //sloped yellow gradient
			game.textures[3][64 * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			game.textures[4][64 * y + x] = 256 * xorcolor;								 //xor green
			game.textures[5][64 * y + x] = 65536 * 192 * (x % 16 && y % 16);			 //red bricks
			game.textures[6][64 * y + x] = 65536 * ycolor;								 //red gradient
			game.textures[7][64 * y + x] = 128 + 256 * 128 + 65536 * 128;				 //flat grey texture
		}
	player_set(&(game.bob), 3, 3);
	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 3, 0, key_release, &game);
	mlx_loop_hook(game.mlx, display_map, &game);
	mlx_loop(game.mlx);
}

/* EOF */
