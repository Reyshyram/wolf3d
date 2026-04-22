/*
** EPITECH PROJECT, 2026
** game_enter.c
** File description:
** Initialize the game scene
*/

#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System/Vector2.h>
#include <string.h>

#include "graphics/engine.h"
#include "graphics/resources.h"

#include "game.h"
#include "wolf3d.h"

static constexpr int WORLD_MAP[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 2, 0, 3, 0, 0, 3, 0, 2, 0, 1, 0, 5, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 2, 0, 3, 0, 0, 3, 0, 2, 0, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 0, 2, 2, 2, 0, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 1},
    {1, 0, 5, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 8, 0, 0, 0, 5, 0, 0, 0, 5, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 5, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 8, 0, 0, 0, 5, 0, 0, 0, 5, 0, 1},
    {1, 0, 5, 5, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 6, 6, 6, 0, 6, 6, 6, 4, 4, 4, 0, 0, 4, 4, 4, 7, 7, 7, 0, 7, 7, 7, 1},
    {1, 6, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 7, 1},
    {1, 6, 0, 8, 0, 8, 0, 6, 4, 0, 0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 0, 7, 1},
    {1, 6, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0, 0, 4, 7, 0, 3, 3, 3, 0, 7, 1},
    {1, 6, 0, 8, 0, 8, 0, 6, 4, 0, 0, 0, 0, 0, 0, 4, 7, 0, 3, 0, 3, 0, 7, 1},
    {1, 6, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0, 0, 4, 7, 0, 3, 3, 3, 0, 7, 1},
    {1, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void game_enter(engine_t *engine)
{
    game_data_t *data = (game_data_t *) engine->scene->data;

    if (!data)
        return;
    memcpy(data->map, WORLD_MAP, sizeof(data->map));
    data->player.pos = (sfVector2f) {15, 15};
    data->player.view_dir = (sfVector2f) {-1, 0};
    data->camera_plane = (sfVector2f) {0, 0.66F};
    data->rays = sfVertexArray_create();
    sfVertexArray_resize(data->rays, (size_t) WIN_WIDTH * 2);
    sfVertexArray_setPrimitiveType(data->rays, sfLines);
    data->wall_textures =
        resources_load_texture(engine->resources, WALL_TEXTURES_PATH);
    sfRenderWindow_setMouseCursorVisible(engine->window, false);
    sfMouse_setPositionRenderWindow(
        (sfVector2i) {WIN_WIDTH / 2, WIN_HEIGHT / 2}, engine->window);
}
