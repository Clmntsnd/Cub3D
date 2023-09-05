#include "../includes/cub3d.h"

/*
**	Function to parse the filemane and ensure that there is
**	the correct extension (".cub").
*/
bool	ft_parse_ext(int ac, char **av)
{
    char *ext; 

	ext = ft_strrchr(av[1], '.');
	if (ac != 2) 
		return (printf("❌ Error\n%s\n%s\n", ERR_ARG, ERR_USG), false);
    if (ext == NULL || ft_strncmp(ext, ".cub", 5) != 0)
        return (printf("❌ Error\n%s\n%s\n", ERR_EXT, ERR_USG), false);
    return (printf("✅ File '%s' has a valid ext!\n", av[1]), true);
}

int	main(int ac, char **av)
{
	if (!ft_parse_ext(ac, av))
		return(1);
	printf("\n🚧 "KYEL"Work In Progress 🚧\n"KRT);
	return (0);
}
