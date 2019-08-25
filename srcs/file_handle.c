#include "wolf.h"

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

static void		content_parse(char *content, t_game *game)
{
	int i;

	i = 0;
    (void)game;
	while (content[i])
	{
		if ((ft_strchr(AUT_CHARS, content[i]) == NULL))
			send_error("Don't put horsesh*t in the file please, thanks.\n");
		i++;
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
	content_parse(content, game);
}
