#include "cub3d.h"

void init_data(t_data *data)
{
	data->config.texture_north = NULL;
	data->config.texture_south = NULL;
	data->config.texture_west = NULL;
	data->config.texture_est = NULL;
	data->config.floor_color = -1;
	data->config.ceiling_color = -1;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
}

static void print_texture(char *name, char *texture)
{
	printf("Texture %s: ", name);
	if (texture)
		printf("%s\n", texture);
	else
		printf("Non définie\n");
}

static void print_textures(t_config *config)
{
	print_texture("Nord", config->texture_north);
	print_texture("Sud", config->texture_south);
	print_texture("Ouest", config->texture_west);
	print_texture("Est", config->texture_est);
}

void print_config(t_config *config)
{
	printf("=== CONFIGURATION ===\n");
	print_textures(config);
	printf("Couleur sol: %d\n", config->floor_color);
	printf("Couleur plafond: %d\n", config->ceiling_color);
	printf("=====================\n");
}

int main(int ac, char **av)
{
    t_data data;
    
    if (ac != 2)
    {
        printf("usage: %s <map.cub>\n", av[0]);
        return (1);
    }   
    init_data(&data);  
    if (parse_file(av[1], &data))
    {
        printf("Erreur pendant le parsing\n");
        cleanup_data(&data);  // Cleanup en cas d'erreur
        return (1);
    }    
    printf("Parsing termine\n");
    find_player(&data);       // Trouvez le joueur
    print_config(&data.config);
    print_map(&data);         // Affichez la carte    
    cleanup_data(&data);      // Cleanup à la fin
    return (0);
}