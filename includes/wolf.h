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

typedef struct		s_vector
{
    double			x;
    double			y;
}					t_vector;

typedef struct		s_player
{
    t_vector		position;
    t_vector		camera;
}					t_player;

typedef struct		s_game
{
    void			*mlx;
    void			*window;
	t_player		bob;
}					t_game;

void                game_init(t_game game);

#endif /* !WOLF_H */

/* EOF */
