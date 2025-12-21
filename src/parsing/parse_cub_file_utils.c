#include "cub3d.h"
/**
 * @brief Advance to the next line in the file.
 *
 * Frees the current line, reads the next line from the file, and
 * increments the line counter.
 *
 * @param line Pointer to the current line buffer.
 * @param fd   File descriptor to read from.
 * @param i    Pointer to current line index (will be incremented).
 */
void	next_line(char **line, int fd, int *i)
{
	free(*line);
	*line = get_next_line(fd);
	(*i)++;
}

/**
 * @brief Check if a line contains only whitespace characters.
 *
 * Iterates through the line and returns false if any non-space char is found.
 *
 * @param line The string to check.
 * @return true if the line is empty or only whitespace, false otherwise.
 */
bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Skip consecutive empty lines in a file while reading.
 *
 * Frees each empty line and reads the next line from the file.
 * Updates the line counter. Returns false if EOF is reached.
 *
 * @param line Pointer to the current line buffer.
 * @param fd   File descriptor to read from.
 * @param i    Pointer to current line index (will be incremented).
 * @return true if a non-empty line is found, false if EOF reached.
 */
bool	skip_empty_lines(char **line, int fd, int *i)
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
