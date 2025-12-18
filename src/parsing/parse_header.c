#include "cub3d.h"

static void	next_line(char **line, int fd, int *i)
{
	free(*line);
	*line = get_next_line(fd);
	(*i)++;
}

static bool	skip_empty_lines(char **line, int fd, int *i)
{
	while (*line && line_is_empty(*line))
	{
		free(*line);
		*line = get_next_line(fd);
		(*i)++;
	}
	if (*line == NULL)
		return (false);
	return (true);
}

static bool	all_headers_set(t_map *map)
{
	int	i;

	i = 0;
	while (i < HEADER_SIZE)
	{
		if (map->id_set[i] == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	set_map_start_line(t_map *map, char **line, int fd, int *i)
{
	if (!all_headers_set(map))
		return (false);
	if (!skip_empty_lines(line, fd, i))
		return (false);
	map->map_start_line = (*i);
	return (true);
}

int	parse_header(const char *path, t_map *map)
{
	int		i;
	int		fd;
	char	*line;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	i = 1;
	while (line)
	{
		if (!skip_empty_lines(&line, fd, &i))
			return (gnl_clear_fd(fd), close(fd), EXIT_FAILURE);
		if (parse_header_line(map, line) == EXIT_FAILURE)
			return (gnl_clear_fd(fd), free(line), close(fd), EXIT_FAILURE);
		next_line(&line, fd, &i);
		if (set_map_start_line(map, &line, fd, &i))
		{
			free(line);
			break ;
		}
	}
	gnl_clear_fd(fd);
	close(fd);
	return (EXIT_SUCCESS);
}
