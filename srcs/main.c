/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:17:28 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/07 21:29:47 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				get_color(t_game *game, uint8_t range, t_point *map)
{
	if (range == 0 && PLAYER_POS.x - map->x < 0)
		return (WHITE);
	else if (range == 0 && PLAYER_POS.x - map->x > 0)
		return (S_GREY);
	else if (range == 1 && PLAYER_POS.y - map->y < 0)
		return (GREY);
	else
		return (VS_GREY);
	return (0x000000);
}

int				close_window(void *param)
{
	(void)param;
	exit(0);
}

int				main(int argc, char *argv[])
{
	t_game		game;

	if (argc != 2)
	{
		ft_putendl("usage: ./wolf3d <map>");
		return (EXIT_FAILURE);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (EXIT_FAILURE == parser(argv[1], &game))
		return (EXIT_FAILURE);
	game_init(game);
	return (EXIT_SUCCESS);
}
