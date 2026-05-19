/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** init_hud
*/

#include <SFML/Graphics/CircleShape.h>
#include <string.h>

#include "game.h"
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "wolf3d.h"

static bool init_minimap(hud_t *hud, unsigned int mini_map_size)
{
    hud->mini_map = sfView_create();
    hud->mini_map_render =
        sfRenderTexture_create(mini_map_size, mini_map_size, false);
    hud->mini_map_shape = sfCircleShape_create();
    hud->mini_map_size = (sfVector2u) {mini_map_size, mini_map_size};
    if (!hud->mini_map || !hud->mini_map_render || !hud->mini_map_shape)
        return false;
    sfCircleShape_setRadius(hud->mini_map_shape, (float) mini_map_size / 2);
    sfCircleShape_setPointCount(hud->mini_map_shape, 100);
    sfCircleShape_setFillColor(hud->mini_map_shape, sfWhite);
    sfCircleShape_setOutlineThickness(hud->mini_map_shape, 2);
    sfCircleShape_setOutlineColor(hud->mini_map_shape,
        sfColor_fromRGBA(0, 0, 0, MINIMAP_OPACITY + 30));
    sfCircleShape_setScale(hud->mini_map_shape, (sfVector2f) {-1, 1});
    return true;
}

static bool init_timer(engine_t *engine, hud_t *hud)
{
    hud->timer = sfText_create();
    if (!hud->timer)
        return false;
    sfText_setFont(hud->timer, engine->default_font);
    sfText_setCharacterSize(hud->timer, WIN_WIDTH / 33.75);
    sfText_setColor(hud->timer, sfWhite);
    sfText_setStyle(hud->timer, sfTextBold);
    sfText_setPosition(hud->timer, TIMER_POS);
    return true;
}

int init_hud(engine_t *engine, game_data_t *data)
{
    sfFloatRect viewport = MINIMAP_VIEWPORT;
    float view_width = (float) WIN_WIDTH * viewport.width;
    float view_height = (float) WIN_HEIGHT * viewport.height;
    unsigned int mini_map_size =
        (unsigned int) (view_width < view_height ? view_width : view_height);

    data->hud = malloc(sizeof(hud_t));
    if (!data->hud)
        return ERROR;
    memset(data->hud, 0, sizeof(*data->hud));
    if (!init_minimap(data->hud, mini_map_size)
        || !init_timer(engine, data->hud)) {
        free_hud(data->hud);
        data->hud = nullptr;
        return ERROR;
    }
    return SUCCESS;
}
