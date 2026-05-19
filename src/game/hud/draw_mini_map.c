/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** mini-map
*/

#include <SFML/Graphics/Color.h>
#include <math.h>

#include "graphics/engine.h"

#include "game.h"
#include "wolf3d.h"

static void set_cell_color(sfRectangleShape *cell, int tile)
{
    switch (tile) {
        case 0:
            sfRectangleShape_setFillColor(cell, sfTransparent);
            break;
        default:
            sfRectangleShape_setFillColor(cell, sfWhite);
            break;
    }
}

static void draw_mm_player(hud_t *hud, game_data_t *d)
{
    sfCircleShape *player = sfCircleShape_create();
    float radius = 2 * MINIMAP_RATIO;
    float cell_size = MINIMAP_TILE_SIZE * MINIMAP_RATIO;

    sfCircleShape_setRadius(player, radius);
    sfCircleShape_setFillColor(player, sfRed);
    sfCircleShape_setPosition(player,
        (sfVector2f) {d->player.pos.x * cell_size - radius,
            d->player.pos.y * cell_size - radius});
    sfRenderTexture_drawCircleShape(hud->mini_map_render, player, NULL);
    sfCircleShape_destroy(player);
}

static void draw_mini_map(hud_t *hud, game_data_t *d)
{
    sfRectangleShape *cell = sfRectangleShape_create();
    float cell_size = MINIMAP_TILE_SIZE * MINIMAP_RATIO;

    sfRectangleShape_setSize(cell, (sfVector2f) {cell_size, cell_size});
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            set_cell_color(cell, d->map[x][y]);
            sfRectangleShape_setPosition(cell,
                (sfVector2f) {(float) x * cell_size, (float) y * cell_size});
            sfRenderTexture_drawRectangleShape(hud->mini_map_render, cell,
                NULL);
        }
    }
    sfRectangleShape_destroy(cell);
}

static void draw_minimap_texture(hud_t *hud, game_data_t *d, float angle)
{
    sfVector2f map_size = {MAP_WIDTH * MINIMAP_TILE_SIZE * MINIMAP_RATIO,
        MAP_HEIGHT * MINIMAP_TILE_SIZE * MINIMAP_RATIO};

    sfView_setCenter(hud->mini_map,
        (sfVector2f) {d->player.pos.x * map_size.x / MAP_WIDTH,
            d->player.pos.y * map_size.y / MAP_HEIGHT});
    sfView_setSize(hud->mini_map, map_size);
    sfView_setRotation(hud->mini_map, angle + 90);
    sfRenderTexture_setView(hud->mini_map_render, hud->mini_map);
    sfRenderTexture_clear(hud->mini_map_render,
        sfColor_fromRGBA(0, 0, 0, MINIMAP_OPACITY));
    draw_mini_map(hud, d);
    draw_mm_player(hud, d);
    sfRenderTexture_display(hud->mini_map_render);
}

static sfVector2f get_minimap_pos(hud_t *hud, const sfFloatRect *viewport)
{
    float width = (float) WIN_WIDTH * viewport->width;
    float height = (float) WIN_HEIGHT * viewport->height;
    float left = (float) WIN_WIDTH * viewport->left;
    float top = (float) WIN_HEIGHT * viewport->top;

    return (sfVector2f) {left + (width - (float) hud->mini_map_size.x) / 2,
        top + (height - (float) hud->mini_map_size.y) / 2};
}

void view_mini_map(engine_t *engine, game_data_t *d, hud_t *hud)
{
    sfFloatRect viewport = MINIMAP_VIEWPORT;
    float angle = atan2f(d->player.view_dir.y, d->player.view_dir.x) * 180
        / (float) M_PI;
    sfVector2f minimap_pos;

    draw_minimap_texture(hud, d, angle);
    minimap_pos = get_minimap_pos(hud, &viewport);
    minimap_pos.x += (float) hud->mini_map_size.x;
    sfCircleShape_setPosition(hud->mini_map_shape, minimap_pos);
    sfCircleShape_setTexture(hud->mini_map_shape,
        sfRenderTexture_getTexture(hud->mini_map_render), true);
    sfRenderWindow_drawCircleShape(engine->window, hud->mini_map_shape, NULL);
}
