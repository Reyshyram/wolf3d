/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** mini-map
*/

#include <math.h>

#include "game.h"

static void set_cell_color(sfRectangleShape *cell, int tile)
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

static void draw_mm_player(engine_t *engine, game_data_t *d)
{
    sfCircleShape *player = sfCircleShape_create();
    float radius = 2 * MINIMAP_RATIO;
    float cell_size = MINIMAP_TILE_SIZE * MINIMAP_RATIO;

    sfCircleShape_setRadius(player, radius);
    sfCircleShape_setFillColor(player, RGB_RED);
    sfCircleShape_setPosition(player,
        (sfVector2f) {d->player.pos.x * cell_size - radius,
            d->player.pos.y * cell_size - radius});
    sfRenderWindow_drawCircleShape(engine->window, player, NULL);
    sfCircleShape_destroy(player);
}

static void draw_mini_map(engine_t *engine, game_data_t *d)
{
    sfRectangleShape *cell = sfRectangleShape_create();
    float cell_size = MINIMAP_TILE_SIZE * MINIMAP_RATIO;

    sfRectangleShape_setSize(cell, (sfVector2f) {cell_size, cell_size});
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            set_cell_color(cell, d->map[x][y]);
            sfRectangleShape_setPosition(cell,
                (sfVector2f) {(float) x * cell_size, (float) y * cell_size});
            sfRenderWindow_drawRectangleShape(engine->window, cell, NULL);
        }
    }
    sfRectangleShape_destroy(cell);
}

void view_mini_map(engine_t *engine, game_data_t *d, hud_t *hud)
{
    sfVector2f map_size = {MAP_WIDTH * MINIMAP_TILE_SIZE * MINIMAP_RATIO,
        MAP_HEIGHT * MINIMAP_TILE_SIZE * MINIMAP_RATIO};
    float angle = atan2pif(d->player.view_dir.y, d->player.view_dir.x) * 180;

    sfView_setCenter(hud->mini_map,
        (sfVector2f) {map_size.x / 2, map_size.y / 2});
    sfView_setSize(hud->mini_map, map_size);
    sfView_setRotation(hud->mini_map, angle + 90);
    sfView_setViewport(hud->mini_map, MINIMAP_VIEWPORT);
    sfRenderWindow_setView(engine->window, hud->mini_map);
    draw_mini_map(engine, d);
    draw_mm_player(engine, d);
    sfRenderWindow_setView(engine->window,
        sfRenderWindow_getDefaultView(engine->window));
}
