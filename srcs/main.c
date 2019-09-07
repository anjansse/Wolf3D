/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:17:28 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/07 16:17:32 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
