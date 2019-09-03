#include "wolf.h"

void		point_set(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

void		point_update(t_point *point, int x, int y)
{
	point->x += x;
	point->y += y;
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

void		player_set(t_player *player, int x, int y)
{
	ft_memset(player, 0, sizeof(t_player));
	vector_set(&(player->pos), x, y);
	vector_set(&(player->dir), -1.0, 0.0);
	vector_set(&(player->plane), 0.0, FOV);
	player->speed = PLAYER_SPEED_REG;
}

/* EOF */
