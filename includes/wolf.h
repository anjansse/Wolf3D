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

# define FOV		60

typedef struct		s_game
{
    void			*mlx;
    void			*window;
}					t_game;

typedef struct      s_vector
{
    double          x;
    double          y;
}                   t_vector;

#endif /* !WOLF_H */

/* EOF */
