/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** mini-map
*/

#include "wolf3d.h"
#include "game.h"

void set_cell_color(sfRectangleShape *cell, int tile)
{
    switch (tile) {
        case 0:
            sfRectangleShape_setFillColor(cell, RGB_NONE);
            break;
        default:
            sfRectangleShape_setFillColor(cell, RGB_WHITE);
            break;
    }
}

void draw_mm_player(engine_t *engine, game_data_t *d)
{
    sfCircleShape *player = sfCircleShape_create();

    sfCircleShape_setRadius(player, 2.f * MINIMAP_RATIO);
    sfCircleShape_setFillColor(player, RGB_RED);
    sfCircleShape_setPosition(player, (sfVector2f)
        {d->player.pos.y * MINIMAP_TILE_SIZE * MINIMAP_RATIO
            - 2.f * MINIMAP_RATIO,
            d->player.pos.x * MINIMAP_TILE_SIZE * MINIMAP_RATIO
            - 2.f * MINIMAP_RATIO});
    sfRenderWindow_drawCircleShape(engine->window, player, NULL);
    sfCircleShape_destroy(player);
}

void draw_mini_map(engine_t *engine, game_data_t *d)
{
    sfRectangleShape *cell = sfRectangleShape_create();

    sfRectangleShape_setSize(cell,
        (sfVector2f){MINIMAP_TILE_SIZE * MINIMAP_RATIO,
            MINIMAP_TILE_SIZE * MINIMAP_RATIO});
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            set_cell_color(cell, d->map[y][x]);
            sfRectangleShape_setPosition(cell,
                (sfVector2f){
                    x * MINIMAP_TILE_SIZE * MINIMAP_RATIO,
                    y * MINIMAP_TILE_SIZE * MINIMAP_RATIO});
            sfRenderWindow_drawRectangleShape(engine->window, cell, NULL);
        }
    }
    sfRectangleShape_destroy(cell);
}

void view_mini_map(engine_t *engine, game_data_t *d, hud_t *hud)
{
    sfView_setCenter(hud->mini_map, (sfVector2f)
        {(MAP_WIDTH * MINIMAP_TILE_SIZE * MINIMAP_RATIO) / 2.f,
            (MAP_HEIGHT * MINIMAP_TILE_SIZE * MINIMAP_RATIO) / 2.f});
    sfView_setSize(hud->mini_map, (sfVector2f)
        {MAP_WIDTH * MINIMAP_TILE_SIZE * MINIMAP_RATIO,
            MAP_HEIGHT * MINIMAP_TILE_SIZE * MINIMAP_RATIO});
    sfView_setRotation(hud->mini_map, 90.f + (90.f * d->player.view_dir.x));
    sfView_setViewport(hud->mini_map,
        (sfFloatRect){0.75f, 0.02f, 0.23f, 0.23f});
    sfRenderWindow_setView(engine->window, hud->mini_map);
    draw_mini_map(engine, d);
    draw_mm_player(engine, d);
    sfRenderWindow_setView(engine->window,
        sfRenderWindow_getDefaultView(engine->window));
}
