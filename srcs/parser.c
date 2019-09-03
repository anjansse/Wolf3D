#include "wolf.h"

static int		parse_line(t_game *game, char *line, int y)
{
	int		i;
	int		j;

	if (line == NULL)
		return (free_map(game->map, y));
	game->map[y] = (uint8_t *)malloc(sizeof(uint8_t) * game->x_max);
	if (game->map[y] == NULL)
		return (free_map(game->map, y));
	i = 0;
	while (line[i] && i < game->x_max)
	{
		if (ft_strchr(FILE_CHAR_MAP, line[i]) == NULL)
			break ;
		game->map[y][i] = line[i] - 48;
		++i;
	}
	j = 0;
	while (line[i + j] == ' ')
		++j;
	if (line[i + j] && line[i + j] != FILE_CHAR_COMMENT)
		j = -1;
	if (j == -1 || i != game->x_max)
		return (free_map(game->map, y + 1));
	return (SUCCESS);
}

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
		line = NULL;
	}
	*str = line;
}

static int		parse_map(int fd, t_game *game, int *nbr)
{
	int		y;
	int		ret;
	char	*line;

	game->map = (uint8_t **)malloc(sizeof(uint8_t *) * game->y_max);
	if (game->map == NULL)
		return (FAILURE);
	y = 0;
	while (y < game->y_max)
	{
		parse_get_line(fd, &line, nbr);
		if (FAILURE == parse_line(game, line, y))
		{
			ft_strdel(&line);
			return (FAILURE);
		}
		ft_strdel(&line);
		line = NULL;
		++y;
	}
	parse_get_line(fd, &line, nbr);
	ret = (line) ? FAILURE : SUCCESS;
	ft_strdel(&line);
	return (ret);
}

static int		parse_size(int fd, t_game *game, int *nbr)
{
	int		ret;
	char	*ptr;
	char	*line;

	line = NULL;
	ret = SUCCESS;
	parse_get_line(fd, &line, nbr);
	if (line == NULL)
		return (FAILURE);
	if ((game->x_max = ft_strtoi(line, &ptr)) <= 0)
		ret = FAILURE;
	if (*ptr != ' ')
		ret = FAILURE;
	if ((game->y_max = ft_strtoi(ptr, &ptr)) <= 0)
		ret = FAILURE;
	while (*ptr && *ptr == ' ')
		++ptr;
	if (*ptr && *ptr != FILE_CHAR_COMMENT)
		ret = FAILURE;
	ft_strdel(&line);
	return (ret);
}

int				parser(char *filename, t_game *game)
{
	int		fd;
	int		ret;
	int		line;

	line = 0;
	if (-1 == (fd = open(filename, O_RDONLY)))
	{
		ft_printf("ERROR: File can't be openned\n");
		return (FAILURE);
	}
	if (FAILURE == (ret = parse_size(fd, game, &line)))
		ft_printf("ERROR: Parse error; line %d\n", line);
	if (ret == SUCCESS && FAILURE == (ret = parse_map(fd, game, &line)))
		ft_printf("ERROR: Parse error; line %d\n", line);
	close(fd);
	return (ret);
}

/* EOF */
