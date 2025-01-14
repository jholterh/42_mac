#include "solong.h"

int xpm_image(t_all *all)
{
    const char *paths[] = {
        "./resources/wall.xpm",
        "./resources/floor.xpm",
        "./resources/player.xpm",
        "./resources/collec.xpm",
        "./resources/exit.xpm"
    };
    void **images[] = {
        &all->img.wall_img,
        &all->img.floor_img,
        &all->img.player_img,
        &all->img.collec_img,
        &all->img.exit_img
    };
    int num_images;

    num_images = sizeof(paths) / sizeof(paths[0]);
    return (load_images(all, paths, images, num_images));
}

int load_images(t_all *all, const char **paths, void ***images, int num_images)
{
    int i;

    i = -1;
    while (++i < num_images)
    {
        *images[i] = mlx_xpm_file_to_image(all->mini.mlx, (char *)paths[i],
                                           &all->mini.img_width, &all->mini.img_height);
        if (!*images[i])
        {
            fprintf(stderr, "Failed to load image: %s\n", paths[i]);
            close_window(all);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

