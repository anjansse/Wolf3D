/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:09:52 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/07 16:10:06 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		free_map(uint8_t **map, size_t size)
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
