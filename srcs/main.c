#include "wolf.h"

void			send_error(char *str)
{
	ft_putstr(str);
	exit(1);
}

static int		filename_parse(char *filename)
{
	int		i;
	int		len;

	i = 0;
	len = (int)ft_strlen(filename);
	if (len < 4)
		send_error("1Wrong file name, please use '.wolf' extansion.\n");
	while (i < len && filename[i] != '.')
		i++;
	if (!ft_strcmp(&filename[i], ".wolf"))
		return (0);
	send_error("Wrong file name, please use '.wolf' extansion.\n");
	return (1);
}	

static void		content_parse(char *content)
{
	while (*content)
	{
		if ((ft_strchr(AUT_CHARS, *content) == NULL))
			send_error("Don't put horsesh*t in the file please, thanks.\n");
		content++;
	}
}

void			file_parse(char *filename, t_game *game)
{
	int 	fd;
	char	*line;
	char	*content;

	(void)game;
	filename_parse(filename);
	if (-1 == (fd = open(filename, O_RDONLY)))
		send_error("File doesn't exist\n");
	while (get_next_line(fd, &line))
		content = ft_strjoin(content, line);
	content_parse(content);
}

int				main(int ac, char **av)
{
	t_game		game;

	if (ac != 2)
		send_error("usage: ./wolf3d <map>\n");
	ft_memset(&game, 0, sizeof(t_game));
	file_parse(av[1], &game);
	// game_init(game);
	return (0);
}

/* EOF */
