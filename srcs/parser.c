#include "wolf.h"

static int		parse_line(t_game *game, char *line, int y)
{
	int		i;
	int		j;

	if (line == NULL)
		return (free_map(game->map, y));
	game->map[y] = (t_uchar *)malloc(sizeof(t_uchar) * game->x_max);
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
		j = 0xFF;
	ft_strdel(&line);
	if (j == 0xFF || i != game->x_max)
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
	}
	*str = line;
}

static int		parse_map(int fd, t_game *game, int *nbr)
{
	int		y;
	int		ret;
	char	*line;

	game->map = (t_uchar **)malloc(sizeof(t_uchar *) * game->y_max);
	if (game->map == NULL)
		return (FAILURE);
	y = 0;
	while (y < game->y_max)
	{
		parse_get_line(fd, &line, nbr);
		if (FAILURE == parse_line(game, line, y))
			return (FAILURE);
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
	char	*ptr;
	char	*line;

	line = NULL;
	parse_get_line(fd, &line, nbr);
	if ((game->x_max = ft_strtoi(line, &ptr)) <= 0)
		return (FAILURE);
	if (*ptr != ' ')
		return (FAILURE);
	if ((game->y_max = ft_strtoi(ptr, &ptr)) <= 0)
		return (FAILURE);
	while (*ptr && *ptr == ' ')
		++ptr;
	if (*ptr && *ptr != FILE_CHAR_COMMENT)
		return (FAILURE);
	ft_strdel(&line);
	return (SUCCESS);
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
