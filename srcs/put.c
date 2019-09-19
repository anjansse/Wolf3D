/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:19:53 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/19 10:55:53 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		put_background(t_game *game, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (i < game->view * SCREEN_WIDTH)
			game->pixels[i] = (i % 4545 != 0) ? 0x000000 : 0xFFFFFF;
		else
			game->pixels[i] = FLOOR;
		++i;
	}
}

void		put_pixel(t_game *game, t_point point, int color)
{
	game->pixels[point.y * SCREEN_WIDTH + point.x] = color;
}

void		put_column(t_game *game, t_point point, size_t size, int color)
{
	size_t		tmp;
	t_point		up_point;

	game->size = size;
	tmp = size / 2;
	point.y = game->view;
	up_point = point;
	while (tmp)
	{
		put_pixel(game, point, color);
		put_pixel(game, up_point, color);
		point.y = (point.y + 1 >= SCREEN_HEIGTH) \
				? SCREEN_HEIGTH - 1 : point.y + 1;
		up_point.y = (up_point.y - 1 <= 0) ? 0 : up_point.y - 1;
		--tmp;
	}
}
