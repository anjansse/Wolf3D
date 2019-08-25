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

# define MAP_WIDTH	8
# define MAP_HEIGTH	8

/*
** Game constraint
**		FOV - Field Of View
**		BLOCK_SIZE - For each element in map
*/

# define FOV			60
# define SCREEN_HEIGTH	900
# define SCREEN_WIDTH	1600
# define BLOCK_SIZE		64
# define AUT_CHARS		" 01\n"

/*
** Colors
*/

# define SKY			0xCDE5FC
# define FLOOR			0xFFCC99

/*
** Game parameters
*/

# define PP_DIMENSION	SCREEN_WIDTH * SCREEN_HEIGTH
# define PP_CENTER		pp_center();
# define PP_DISTANCE	(SCREEN_WIDTH / 2) / tan(FOV / 2)
# define PP_UNIT		FOV / SCREEN_WIDTH

/*
**	Access of structure shortcut.
*/

# define PLAYER			game->bob

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_player
{
	t_vector		position;
	double			direction;
}					t_player;

typedef struct		s_map
{
	int				**map;
}					t_map;

typedef struct		s_game
{
	void			*mlx;
	void			*window;
	void			*image;
	unsigned int	*pixels;
	t_map			coord;
	t_player		bob;
}					t_game;

void				game_init(t_game game);
void				put_background(t_game game, size_t size);
void				put_pixel(t_game game, t_vector point, int color);
void				put_column(t_game game, t_vector point, size_t size, int color);
void				file_parse(char *filename, t_game *game);
void				ft_free_db_tab(char **av);
void				ft_free_db_tab_int(int **av);
void				send_error(char *str);

#endif /* !WOLF_H */

/* EOF */
