#ifndef WOLF_H
# define WOLF_H

# include "libft.h"
# include "mlx.h"
# include "key_mapping.h"

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1

/*
** Game constraint
**		FOV - Field Of View
**		BLOCK_SIZE - For each element in map
*/

# define FOV			60
# define SCREEN_HEIGTH	900
# define SCREEN_WIDTH	1600
# define BLOCK_SIZE		64
# define NB_TEXTURES	2

# define FILE_CHAR_MAP		"01"
# define FILE_CHAR_COMMENT	'#'

# define PLAYER_SPEED_REG	1.0
# define PLAYER_SPEED_RUN	1.25

/*
** Colors
*/

# define SKY			0x151A4F
# define FLOOR			0x4E4E4F

/*
** Game parameters
*/

# define PP_DIMENSION	SCREEN_WIDTH * SCREEN_HEIGTH
# define PP_CENTER		pp_center();
# define PP_DISTANCE	(SCREEN_WIDTH / 2) / tan(FOV / 2 * M_PI / 180)
# define PP_UNIT		FOV / SCREEN_WIDTH

/*
** Access of structure shortcut.
*/

# define PLAYER		game->bob

typedef unsigned char	t_uchar;

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

/*
** The Player
** 	position: vector position on the map;
** 	theta: angle goes from 0 to 359.9 need to remains positif
**		   angle   0 means look on the east
**		   angle  90 means look on the south
**		   angle 180 means look on the west
**		   angle 270 means look on the north
*/

// typedef struct		s_map
// {
// 	t_uchar			c;
// 	int				texture;
// }					t_map;

typedef struct		s_player
{
	t_vector		position;
	float			theta;
	float			speed;
}					t_player;

typedef struct		s_game
{
	t_player		bob;
	void			*mlx;
	void			*window;
	void			*image;
	unsigned int	*pixels;
	t_uchar			**map;
	int				x_max;
	int				y_max;
	void			*texture;
	t_uchar			should_draw;
}					t_game;

void				game_init(t_game game);
void				get_texture(t_game *game);

void				put_background(t_game *game, size_t size);
void				put_pixel(t_game *game, t_vector point, int color);
void				put_column(t_game *game, t_vector point, size_t size, int color);

int					parser(char *filename, t_game *game);

int					free_map(t_uchar **map, size_t size);

int					key_press(int key, void *param);
int					key_release(int key, void *param);

int					point_is_wall(t_game *game, t_vector point, int *wall);
void				point_set(t_vector *point, double x, double y);
void				point_update(t_vector *point, double theta, double x, double y);
void				point_move(t_game *game, t_vector *point, double x, double y);

double				wall_distance(t_game *game, float theta);
// double				get_distance(t_game *game, double angle)

#endif /* !WOLF_H */

/* EOF */
