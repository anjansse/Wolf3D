#include "wolf.h"

int		free_map(t_uchar **map, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(map[i]);
		map[i] = NULL;
		++i;
	}
	free(map);
	map = NULL;
	return (EXIT_FAILURE);
}

/* EOF */
