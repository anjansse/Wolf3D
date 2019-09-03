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
# include <sys/time.h>

# define SUCCESS 0
# define FAILURE 1

# define FOV			0.60
# define ROTATION_SPEED	0.0625
# define SCREEN_HEIGTH	900
# define SCREEN_WIDTH	1600
# define PP_DIMENSION	SCREEN_WIDTH * SCREEN_HEIGTH

# define FILE_CHAR_MAP		"01"
# define FILE_CHAR_COMMENT	'#'

# define PLAYER_SPEED_REG	0.125
# define PLAYER_SPEED_RUN	0.5

/*
** Colors
*/

# define SKY			0x151A4F
# define FLOOR			0x4E4E4F

/*
** Access of structure shortcut.
*/

# define PLAYER_POS		game->bob.pos
# define PLAYER_DIR		game->bob.dir
# define PLAYER_PL		game->bob.plane

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_player
{
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	float			speed;
}					t_player;

typedef struct		s_game
{
	t_player		bob;
	t_point			step;
	void			*mlx;
	void			*window;
	void			*image;
	uint32_t		*pixels;
	uint8_t			**map;
	int				x_max;
	int				y_max;
	void			*texture;
	uint8_t			draw;
}					t_game;

void				game_init(t_game game);
void				get_texture(t_game *game);

void				put_background(t_game *game, size_t size);
void				put_pixel(t_game *game, t_point point, int color);
void				put_column(t_game *game, t_point point, size_t size, int color);

int					parser(char *filename, t_game *game);

int					free_map(uint8_t **map, size_t size);

int					key_press(int key, void *param);
int					key_release(int key, void *param);

void				point_set(t_point *point, int x, int y);
void				vector_set(t_vector *point, double x, double y);
void				player_set(t_player *player, int x, int y);

#endif /* !WOLF_H */

/* EOF */
