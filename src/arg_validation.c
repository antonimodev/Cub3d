#include "cub3d.h"

bool	validate_args(int ac, char **av)
{
    if (!validate_arg_num(ac))
		return (false);
	if (!validate_map_extension(av[1]))
		return (false);
	if (!validate_file_access(av[1]))
		return (false);
	return (true);
}

static bool	validate_arg_num(int ac)
{
	if (ac < 2)
	{
		write_error("No arguments provided. Usage: ./cub3d <map_file.cub>");
		return (false);
	}
	else if (ac > 2)
	{
		write_error("Too many arguments. Usage: ./cub3d <map_file.cub>");
		return (false);
	}
	return (true);
}

static bool	validate_map_extension(const char *filename)
{
    char    *file_extension;
    
    file_extension = ft_strchr(filename, '.');
	if (!file_extension)
	{
		write_error("File has no extension. Expected .cub");
		return (false);
	}
    if (ft_strcmp(file_extension, ".cub") != 0)
    {
        write_error("Invalid file extension. Expected .cub");
        return (false);
    }
    return (true);
}

bool	validate_file_access(const char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write_error("File cannot be opened or doesn't exist");
        return (false);
    }
    close(fd);
    return (true);
}
