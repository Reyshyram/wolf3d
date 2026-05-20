/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** init_hud
*/

#include <SFML/Graphics/CircleShape.h>
#include <string.h>

#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/sprite_anim.h"

#include "game.h"
#include "weapons.h"
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

static bool init_cursor(engine_t *engine, hud_t *hud)
{
    sprite_frame_info_t frame_info = {
        (sfIntRect) {0, 0, CURSOR_WIDTH, CURSOR_HEIGHT}, CURSOR_FRAME_COUNT,
        CURSOR_ANIMATION_FPS};
    float scale = CURSOR_SIZE / (float) CURSOR_WIDTH;

    hud->cursor = sprite_anim_create(CURSOR_PATH, &frame_info, engine);
    if (!hud->cursor)
        return false;
    sfSprite_setScale(hud->cursor->sprite, (sfVector2f) {scale, scale});
    sfSprite_setOrigin(hud->cursor->sprite,
        (sfVector2f) {(float) CURSOR_WIDTH / 2.0F,
            (float) CURSOR_HEIGHT / 2.0F});
    return true;
}

static bool init_ammo_sprite(engine_t *engine, hud_t *hud)
{
    sfTexture *texture =
        resources_load_texture(engine->resources, AMMO_ICON_PATH);
    sfVector2u size;
    float scale;

    if (!texture)
        return false;
    hud->ammo_sprite = sfSprite_create();
    if (!hud->ammo_sprite)
        return false;
    size = sfTexture_getSize(texture);
    scale = (HUD_AMMO_ICON_HEIGHT * HUD_SCALE) / (float) size.y;
    sfSprite_setTexture(hud->ammo_sprite, texture, true);
    sfSprite_setScale(hud->ammo_sprite, (sfVector2f) {scale, scale});
    sfSprite_setOrigin(hud->ammo_sprite,
        (sfVector2f) {(float) size.x / 2.0F, (float) size.y / 2.0F});
    return true;
}

static bool init_ammo_texts(engine_t *engine, hud_t *hud)
{
    unsigned int main_size = (unsigned int) (HUD_AMMO_SIZE * HUD_SCALE);

    hud->hud_font = resources_load_font(engine->resources, HUD_FONT_PATH);
    if (!hud->hud_font)
        return false;
    hud->ammo_text = sfText_create();
    if (!hud->ammo_text)
        return false;
    sfText_setFont(hud->ammo_text, hud->hud_font);
    sfText_setCharacterSize(hud->ammo_text, main_size);
    sfText_setColor(hud->ammo_text, sfWhite);
    return true;
}

static bool init_timer(hud_t *hud)
{
    hud->timer = sfText_create();
    if (!hud->timer)
        return false;
    sfText_setFont(hud->timer, hud->hud_font);
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
        || !init_ammo_texts(engine, data->hud) || !init_timer(data->hud)
        || !init_cursor(engine, data->hud)
        || !init_ammo_sprite(engine, data->hud)) {
        free_hud(data->hud);
        data->hud = nullptr;
        return ERROR;
    }
    return SUCCESS;
}
