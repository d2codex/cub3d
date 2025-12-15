#include "cub3d.h"

static const t_header_entry	*get_header_table(size_t *count)
{
	static const t_header_entry	header[] = {
	{"NO", ID_NO, 2},
	{"SO", ID_SO, 2},
	{"WE", ID_WE, 2},
	{"EA", ID_EA, 2},
	{"F", ID_FLOOR, 1},
	{"C", ID_CEILING, 1},
	};

	if (count)
		*count = sizeof(headers) / sizeof(headers[0]);
	return (header_entry);
}

static t_header_type	*get_header_entry(const char *line)
{
	size_t					i;
	size_t					count;
	const t_header_entry	*entries;

	entries = get_header_table(&count);
	i = 0;
	while (i < count)
	{
		if (!ft_strncmp(line, entries[i].key, entries[i].len)
			&& ft_isspace(line[entries[i].len]))
			return (&entries[i]);
		i++;
	}
	return (NULL);
}

static int	parse_header_value(t_map *map, const char *value, t_header_type id)
{
	char	*trimmed_value;
	int		*target_color;

	if (map->id_set[id] == true)
		return (print_errors("duplicate identifier"), EXIT_FAILURE);
	trimmed_value = ft_strtrim(value, " \t\n");
	if (!trimmed_value || trimmed_value[0] == '\0')
		return (free(trimmed_value), EXIT_FAILURE);
	if (id >= ID_NO && id <= ID_EA)
		map->tex_paths[id] = trimmed_value; //pointers will need to be freed eventually
	else
	{
		if (id == ID_FLOOR)
			target_color = map->floor_color;
		else
			target_color = map->ceiling_color;
		if (parse_rgb(trimmed_value, target_color) == EXIT_FAILURE)
		{
			print_errors("rgb");
			return (free(trimmed_value), EXIT_FAILURE);
		}
		free(trimmed_value);
	}
	map->id_set[id] = true;
	return (EXIT_SUCCESS);
}

int	parse_header_line(t_map *map, char *line)
{
	int				i;
	t_header_type	*entry;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	entry = get_header_entry(line + i);
	if (!entry)
		return (EXIT_FAILURE);
	i += entry->len;
	if (!ft_isspace(line[i]))
		return (EXIT_FAILURE);
	if (parse_header_value(map, line + i, entry->id) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
