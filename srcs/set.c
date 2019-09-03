#include "wolf.h"

void			player_init(t_player *player, int x, int y)
{
	ft_memset(player, 0, sizeof(t_player));
	player->pos.x = x;
	player->pos.y = y;
	player->dir.x = -1;
	player->plane.y = 0.60;
	player->speed = PLAYER_SPEED_REG;
	player->frame = 0.0625;
}

void		vector_set(t_vector *point, double x, double y)
{
	point->x = x;
	point->y = y;
}

void		point_set(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

/* EOF */
