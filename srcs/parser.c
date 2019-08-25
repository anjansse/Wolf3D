#include "wolf.h"

static int		parse_extension(char *filename)
{
	char	*extension;

	extension = ft_strchr(filename, '.');
	if (extension == NULL)
		return (EXIT_FAILURE);
	if (ft_strcmp(extension, FILE_EXTENSION) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

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
	return (EXIT_SUCCESS);
}

static int		parse_map(int fd, t_game *game, int *nbr)
{
	int		y;
	char	*line;

	game->map = (t_uchar **)malloc(sizeof(t_uchar *) * game->y_max);
	if (game->map == NULL)
		return (EXIT_FAILURE);
	y = 0;
	while (y < game->y_max)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0 && line)
		{
			++(*nbr);
			if (*line != FILE_CHAR_COMMENT)
				break ;
			ft_strdel(&line);
		}
		if (EXIT_FAILURE == parse_line(game, line, y))
			return (EXIT_FAILURE);
		++y;
	}
	while (get_next_line(fd, &line) >= 0 && line)
	{
		++(*nbr);
		if (*line != FILE_CHAR_COMMENT)
		{
			ft_strdel(&line);
			return (EXIT_FAILURE);
		}
		ft_strdel(&line);
	}
	return (EXIT_SUCCESS);
}

static int		parse_size(int fd, t_game *game, int *nbr)
{
	char	*ptr;
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		++(*nbr);
		if (*line != FILE_CHAR_COMMENT)
			break ;
		ft_strdel(&line);
	}
	if ((game->x_max = ft_strtoi(line, &ptr)) <= 0)
		return (EXIT_FAILURE);
	if (*ptr != ' ')
		return (EXIT_FAILURE);
	if ((game->y_max = ft_strtoi(ptr, &ptr)) <= 0)
		return (EXIT_FAILURE);
	while (*ptr && *ptr == ' ')
		++ptr;
	if (*ptr && *ptr != FILE_CHAR_COMMENT)
		return (EXIT_FAILURE);
	ft_strdel(&line);
	return (EXIT_SUCCESS);
}

int				parser(char *filename, t_game *game)
{
	int		fd;
	int		line;

	line = 0;
	if (EXIT_FAILURE == parse_extension(filename))
		send_error("ERROR: Extension is invalid\n");
	if (-1 == (fd = open(filename, O_RDONLY)))
	{
		ft_printf("ERROR: File can't be openned\n");
		return (EXIT_FAILURE);
	}
	if (EXIT_FAILURE == parse_size(fd, game, &line))
	{
		close(fd);
		ft_printf("ERROR: Parse error; line %d\n", line);
		return (EXIT_FAILURE);
	}
	if (EXIT_FAILURE == parse_map(fd, game, &line))
	{
		close(fd);
		ft_printf("ERROR: Parse error; line %d\n", line);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

/* EOF */
