#include "wolf.h"

static void	player_update(t_game *game, t_player *player, double x, double y)
{
	int			x_new;
	int			y_new;
	t_vector	point;

	vector_set(&point, player->pos.x + x, player->pos.y + y);
	x_new = (int)floor(point.x);
	y_new = (int)floor(point.y);
	if (0 <= x_new && x_new < game->x_max && 0 <= y_new && y_new < game->y_max)
	{
		if (game->map[y_new][x_new] == 0)
			vector_set(&(player->pos), point.x, point.y);
	}
}

void		player_set(t_player *player, int x, int y)
{
	(void)x;
	(void)y;
	vector_set(&(player->dir), -1.0, 0.0);
	vector_set(&(player->plane), 0.0, FOV);
	player->speed = PLAYER_SPEED_REG;
}

void		player_rotation(t_game *game)
{
	double		speed;
	double		player_pl_x;
	double		player_dir_x;

	if (game->move & ROTATE_LEFT || game->move & ROTATE_RIGTH)
	{
		player_pl_x = PLAYER_PL.x;
		player_dir_x = PLAYER_DIR.x;
		speed = (game->move & ROTATE_LEFT) ? SPEED_ROTATION : -SPEED_ROTATION;
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
	if (game->move & MOVE_FRONT)
	{
		player_update(game, &(game->bob), (PLAYER_DIR.x * speed), 0);
		player_update(game, &(game->bob), 0, (PLAYER_DIR.y * speed));
	}
	if (game->move & MOVE_BACK)
	{
		player_update(game, &(game->bob), -(PLAYER_DIR.x * speed), 0);
		player_update(game, &(game->bob), 0, -(PLAYER_DIR.y * speed));
	}
	if (game->move & MOVE_LEFT)
	{
		player_update(game, &(game->bob), -(PLAYER_DIR.y * speed), 0);
		player_update(game, &(game->bob), 0, (PLAYER_DIR.x * speed));
	}
	if (game->move & MOVE_RIGHT)
	{
		player_update(game, &(game->bob), (PLAYER_DIR.y * speed), 0);
		player_update(game, &(game->bob), 0, -(PLAYER_DIR.x * speed));
	}
}

/* EOF */
