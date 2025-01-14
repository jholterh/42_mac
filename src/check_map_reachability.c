#include "solong.h"

int check_map_reachability(t_maps maps, t_game game)
{
    char **temp = create_map_copy(maps);
    
    if (!temp)
        return 1;
    perform_flood_fill(temp, game.player_x, game.player_y);
    if (verify_flood_fill(temp, maps.rows))
    {
        free_string(temp, maps.rows);
        return 1;
    }
    free_string(temp, maps.rows);
    return 0;
}

char **create_map_copy(t_maps maps)
{
    char **temp;
    int i;

    temp = malloc(maps.rows * sizeof(char *));
    if (!temp)
    {
        perror("Failed to allocate memory for temp map");
        return NULL;
    }
    i = -1;
    while (++i < maps.rows)
    {
        temp[i] = strdup(maps.map[i]);
        if (!temp[i])
        {
            perror("Failed to duplicate map line");
            free_string(temp, i);
            return NULL;
        }
    }
    return temp;
}

void perform_flood_fill(char **temp, int x, int y)
{
    if (temp[y][x] == '1' || temp[y][x] == '2')
        return ;
    temp[y][x] = '2';
    perform_flood_fill(temp, x, y + 1);
    perform_flood_fill(temp, x, y - 1);
    perform_flood_fill(temp, x + 1, y);
    perform_flood_fill(temp, x - 1, y);
}

int verify_flood_fill(char **temp, int rows)
{
    int i;
    int j;

    i = -1;
    while (++i < rows)
    {
        j = -1;
        while (temp[i][++j]) {
            if (!(strchr("012", temp[i][j])))
            {
                printf("Flood has not passed\n");
                return 1;
            }
        }
    }
    return 0;
}
