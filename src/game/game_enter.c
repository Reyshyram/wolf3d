/*
** EPITECH PROJECT, 2026
** game_enter.c
** File description:
** Initialize the game scene
*/

#include <SFML/Graphics/Glsl.h>
#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Shader.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/Graphics/View.h>
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

static void set_up_floor_ceil(game_data_t *data)
{
    sfVector2u textures_size = {NB_WALL_TEXTURES * WALL_TEXTURE_WIDTH,
        WALL_TEXTURE_HEIGHT};

    data->floor_ceil_shader =
        sfShader_createFromFile(nullptr, nullptr, FLOOR_CEIL_SHADER_PATH);
    data->floor_ceil = sfRectangleShape_create();
    sfRectangleShape_setSize(data->floor_ceil,
        (sfVector2f) {(float) WIN_WIDTH, (float) WIN_HEIGHT});
    sfShader_setTextureUniform(data->floor_ceil_shader, "u_textures",
        data->wall_textures);
    sfShader_setVec2Uniform(data->floor_ceil_shader, "u_resolution",
        (sfGlslVec2) {(float) WIN_WIDTH, (float) WIN_HEIGHT});
    sfShader_setVec2Uniform(data->floor_ceil_shader, "u_textures_size",
        (sfGlslVec2) {(float) textures_size.x, (float) textures_size.y});
    sfShader_setFloatUniform(data->floor_ceil_shader, "u_tile_size",
        (float) WALL_TEXTURE_WIDTH);
    sfShader_setFloatUniform(data->floor_ceil_shader, "u_floor_index",
        FLOOR_TILE_INDEX);
    sfShader_setFloatUniform(data->floor_ceil_shader, "u_ceil_index",
        CEIL_TILE_INDEX);
}

static void init_player(game_data_t *data)
{
    data->player.pos = (sfVector2f) {15, 15};
    data->player.view_dir = (sfVector2f) {-1, 0};
    data->camera_plane = (sfVector2f) {0, DEFAULT_FOV};
    data->camera_plane_base = (sfVector2f) {0, 1.0F};
    data->fov = DEFAULT_FOV;
}

void game_enter(engine_t *engine)
{
    game_data_t *data = (game_data_t *) engine->scene->data;

    if (!data)
        return;
    memcpy(data->map, WORLD_MAP, sizeof(data->map));
    init_player(data);
    data->rays = sfVertexArray_create();
    sfVertexArray_resize(data->rays, (size_t) WIN_WIDTH * 2);
    sfVertexArray_setPrimitiveType(data->rays, sfLines);
    data->wall_textures =
        resources_load_texture(engine->resources, WALL_TEXTURES_PATH);
    set_up_floor_ceil(data);
    sfRenderWindow_setMouseCursorVisible(engine->window, false);
    sfMouse_setPositionRenderWindow(
        (sfVector2i) {WIN_WIDTH / 2, WIN_HEIGHT / 2}, engine->window);
    data->camera =
        sfView_createFromRect((sfFloatRect) {0, 0, WIN_WIDTH, WIN_HEIGHT});
    data->render_texture =
        sfRenderTexture_create(WIN_WIDTH, WIN_HEIGHT, false);
}
