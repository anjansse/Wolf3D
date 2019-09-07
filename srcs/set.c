/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:22:02 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/07 16:22:23 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
