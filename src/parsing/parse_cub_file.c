#include "cub3d.h"

static void	update_map_dimensions(t_map *map, const char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len > map->width)
		map->width = len;
	map->height++;
}

static bool	line_starts_with_map(const char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '1')
		return (false);
	return (true);
}

static int	parse_headers(int fd, char **line, int *i, t_map *map)
{
	while (*line)
	{
		skip_empty_lines(line, fd, i);
		if (map->header_line_count == HEADER_SIZE)
			return (EXIT_SUCCESS);
		if (parse_header_line(map, *line) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		free(*line);
		*line = get_next_line(fd);
		(*i)++;
	}
	return (EXIT_FAILURE);
}

static int	parse_map(int fd, char **line, int *i, t_map *map)
{
	skip_empty_lines(line, fd, i);
	if (!line_starts_with_map(*line))
	{
		print_errors(MAP_INVALID_START, NULL, NULL);
		return (EXIT_FAILURE);
	}
	map->map_start_line = *i;
	while (*line)
	{
		update_map_dimensions(map, *line);
		free(*line);
		*line = get_next_line(fd);
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

int	parse_cub_file(const char *path, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	i = 0;
	line = get_next_line(fd);
	if (parse_headers(fd, &line, &i, map) == EXIT_FAILURE)
	{
		free(line);
		close(fd);
		return (EXIT_FAILURE);
	}
	if (parse_map(fd, &line, &i, map) == EXIT_FAILURE)
	{
		free(line);
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
