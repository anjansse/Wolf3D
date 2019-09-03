#include "wolf.h"

static void	player_update(t_game *game, t_player *player, double x, double y)
{
	t_vector	point;

	vector_set(&point, player->pos.x + x, player->pos.y + y);
	if (0 <= point.x && point.x < game->x_max)
	{
		if (game->map[(int)floor(point.y)][(int)floor(point.x)] == 0)
			vector_set(&(player->pos), point.x, point.y);
	}
}

void		player_set(t_player *player, int x, int y)
{
	ft_memset(player, 0, sizeof(t_player));
	vector_set(&(player->pos), x, y);
	vector_set(&(player->dir), -1.0, 0.0);
	vector_set(&(player->plane), 0.0, FOV);
	player->speed = PLAYER_SPEED_REG;
}

void		player_rotation(t_game *game)
{
	double		speed;
	double		player_pl_x;
	double		player_dir_x;

	if (game->move.l_rotate == 1 || game->move.r_rotate == 1)
	{
		player_pl_x = PLAYER_PL.x;
		player_dir_x = PLAYER_DIR.x;
		speed = (game->move.l_rotate) ? SPEED_ROTATION : -SPEED_ROTATION;
		PLAYER_PL.x = PLAYER_PL.x * cos(speed) - PLAYER_PL.y * sin(speed);
		PLAYER_PL.y = player_pl_x * sin(speed) + PLAYER_PL.y * cos(speed);
		PLAYER_DIR.x = PLAYER_DIR.x * cos(speed) - PLAYER_DIR.y * sin(speed);
		PLAYER_DIR.y = player_dir_x * sin(speed) + PLAYER_DIR.y * cos(speed);
	}
}

void		player_movement(t_game *game)
{
	double		speed;

	speed = SPEED_MOVEMENT * PLAYER_SPEED;
	if (game->move.front == 1)
	{
		player_update(game, &(game->bob), (PLAYER_DIR.x * speed), 0);
		player_update(game, &(game->bob), 0, (PLAYER_DIR.y * speed));
	}
	if (game->move.back == 1)
	{
		player_update(game, &(game->bob), -(PLAYER_DIR.x * speed), 0);
		player_update(game, &(game->bob), 0, -(PLAYER_DIR.y * speed));
	}
	if (game->move.left == 1)
	{
		player_update(game, &(game->bob), -(PLAYER_DIR.y * speed), 0);
		player_update(game, &(game->bob), 0, (PLAYER_DIR.x * speed));
	}
	if (game->move.rigth == 1)
	{
		player_update(game, &(game->bob), (PLAYER_DIR.y * speed), 0);
		player_update(game, &(game->bob), 0, -(PLAYER_DIR.x * speed));
	}
}

/* EOF */
