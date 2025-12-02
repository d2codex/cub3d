#include "cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	printf("Test 1: %s\n", get_file_basename("/home/user/test.cub"));
	printf("Test 2: %s\n", get_file_basename("./maps/test.cub"));
	printf("Test 3: %s\n", get_file_basename("test.cub"));
	printf("Test 4: %s\n", get_file_basename("maps/.hidden.cub"));
	printf("Test 4: %s\n", get_file_basename(".cub"));

	return (0);
}
