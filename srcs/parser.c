/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 22:36:10 by mjacques          #+#    #+#             */
/*   Updated: 2019/09/07 22:36:11 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		parse_get_line(int fd, char **str, int *nbr)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0 && line)
	{
		++(*nbr);
		if (*line && *line != FILE_CHAR_COMMENT)
			break ;
		ft_strdel(&line);
	}
	*str = line;
}

static uint8_t	parse_line(t_game *game, char *line, int y, uint8_t *p)
{
	int		i;

	i = 0;
	while (*line && i < game->x_max)
	{
		if (ft_strchr(FILE_CHAR_MAP, *line) == NULL)
			break ;
		if (*line == FILE_CHAR_PLAYER)
		{
			if (*p == SUCCESS)
				return (FAILURE);
			*p = SUCCESS;
			vector_set(&(game->bob.pos), i, y);
		}
		game->map[y][i] = (*line == FILE_CHAR_PLAYER) ? 0 : *line - 48;
		++line;
		++i;
	}
	while (*line && *line == ' ')
		++line;
	if (*line && *line != FILE_CHAR_COMMENT)
		return (FAILURE);
	if (i != game->x_max)
		return (FAILURE);
	return (SUCCESS);
}

static uint8_t	parse_map(int fd, t_game *game, int *nbr)
{
	int		y;
	char	*line;
	uint8_t	ret;
	uint8_t	player;

	ret = SUCCESS;
	player = FAILURE;
	if (!(game->map = (uint8_t **)malloc(sizeof(uint8_t *) * game->y_max)))
		return (FAILURE);
	y = 0;
	while (SUCCESS == ret && y < game->y_max)
	{
		if (!(game->map[y] = (uint8_t *)malloc(sizeof(uint8_t) * game->x_max)))
			return (free_map(game->map, y));
		parse_get_line(fd, &line, nbr);
		if (line)
			ret = parse_line(game, line, y, &player);
		ft_strdel(&line);
		++y;
	}
	if (FAILURE == player || FAILURE == ret)
		free_map(game->map, y);
	return ((FAILURE == player) ? FAILURE : ret);
}

static uint8_t	parse_size(int fd, t_game *game, int *nbr)
{
	int		ret;
	char	*tmp;
	char	*line;

	line = NULL;
	ret = SUCCESS;
	parse_get_line(fd, &line, nbr);
	if (line == NULL)
		return (FAILURE);
	if ((game->x_max = ft_strtoi(line, &tmp)) <= 0)
		ret = FAILURE;
	if (*tmp != ' ')
		ret = FAILURE;
	if ((game->y_max = ft_strtoi(tmp, &tmp)) <= 0)
		ret = FAILURE;
	while (*tmp && *tmp == ' ')
		++tmp;
	if (*tmp && *tmp != FILE_CHAR_COMMENT)
		ret = FAILURE;
	ft_strdel(&line);
	return (ret);
}

int				parser(char *filename, t_game *game)
{
	int		fd;
	int		line;
	char	*str;
	uint8_t	ret;

	line = 0;
	str = NULL;
	if (-1 == (fd = open(filename, O_RDONLY)))
	{
		ft_printf("ERROR: File can't be openned\n");
		return (FAILURE);
	}
	if (FAILURE == (ret = parse_size(fd, game, &line)))
		ft_printf("ERROR: Parse error; line %d\n", line);
	if (SUCCESS == ret && FAILURE == (ret = parse_map(fd, game, &line)))
		ft_printf("ERROR: Parse error; line %d\n", line);
	if (SUCCESS == ret)
		parse_get_line(fd, &str, &line);
	if (str)
		ret = FAILURE;
	ft_strdel(&str);
	close(fd);
	return (ret);
}
