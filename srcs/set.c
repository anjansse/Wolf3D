#include "wolf.h"

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
