/*
** EPITECH PROJECT, 2026
** draw_weapon_hud.c
** File description:
** Draw weapon hud and crosshair
*/

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/System/Vector2.h>
#include <stdio.h>

#include "graphics/engine.h"
#include "graphics/sprite_anim.h"

#include "game.h"
#include "weapons.h"
#include "wolf3d.h"

static void draw_cursor(engine_t *engine, hud_t *hud)
{
    sfVector2f center = {(float) engine->window_size.x / 2.0F,
        (float) engine->window_size.y / 2.0F};

    sfSprite_setPosition(hud->cursor->sprite, center);
    sfRenderWindow_drawSprite(engine->window, hud->cursor->sprite, nullptr);
}

// clang-format off
static void get_layout(engine_t *engine, weapon_t *weapon,
    hud_layout_t *layout)
{
    float scale = HUD_SCALE;
    float x = HUD_WEAPON_GAP_X * scale;
    float y = HUD_WEAPON_GAP_Y * scale;

    layout->scale = scale;
    layout->bounds = sfSprite_getGlobalBounds(weapon->ui_sprite);
    layout->pos = (sfVector2f) {(float) engine->window_size.x - x
        - layout->bounds.width / 2.0F,
        (float) engine->window_size.y - y - layout->bounds.height / 2.0F};
}
// clang-format on

static void update_ammo_text(hud_t *hud, weapon_t *w)
{
    char buff[32];

    if (w->is_reloading)
        snprintf(buff, sizeof(buff), "RELOADING");
    else if (w->type == WEAPON_GRENADE)
        snprintf(buff, sizeof(buff), "x%d", w->ammo);
    else
        snprintf(buff, sizeof(buff), "%d/%d", w->ammo,
            w->weapon_data->max_ammo);
    sfText_setString(hud->ammo_text, buff);
}

static void get_ammo_positions(hud_t *hud, const hud_layout_t *layout,
    sfVector2f *text_pos, sfVector2f *sprite_pos)
{
    sfFloatRect text_bounds = sfText_getLocalBounds(hud->ammo_text);
    sfFloatRect ammo_bounds = sfSprite_getGlobalBounds(hud->ammo_sprite);
    float weapon_bottom = layout->pos.y + layout->bounds.height / 2.0F;
    float y = weapon_bottom + HUD_TEXT_ROW_GAP * layout->scale;
    float text_right = layout->pos.x + layout->bounds.width / 2.0F;

    text_pos->x = text_right - text_bounds.width - text_bounds.left;
    text_pos->y = y - text_bounds.top;
    sprite_pos->x =
        text_pos->x - (HUD_TEXT_ICON_GAP * layout->scale) - ammo_bounds.width;
    sprite_pos->y = y + (text_bounds.height / 2.0F);
}

static void draw_active_weapon_hud(engine_t *engine, game_data_t *d,
    hud_layout_t *layout)
{
    weapon_t *w = &d->weapons[d->active_weapon];
    sfVector2f text_pos;
    sfVector2f sprite_pos;

    sfSprite_setPosition(w->ui_sprite, layout->pos);
    sfRenderWindow_drawSprite(engine->window, w->ui_sprite, nullptr);
    update_ammo_text(d->hud, w);
    get_ammo_positions(d->hud, layout, &text_pos, &sprite_pos);
    sfText_setPosition(d->hud->ammo_text, text_pos);
    sfSprite_setPosition(d->hud->ammo_sprite, sprite_pos);
    sfRenderWindow_drawSprite(engine->window, d->hud->ammo_sprite, nullptr);
    sfRenderWindow_drawText(engine->window, d->hud->ammo_text, nullptr);
}

// clang-format off
static void draw_inactive_weapon_hud(engine_t *engine, game_data_t *d,
    hud_layout_t *layout)
{
    int index = (d->active_weapon == WEAPON_SLOT_MAIN) ? WEAPON_SLOT_GRENADE
        : WEAPON_SLOT_MAIN;
    weapon_t *w = &d->weapons[index];
    sfVector2f prev_scale = sfSprite_getScale(w->ui_sprite);
    sfVector2f small_scale = {prev_scale.x * HUD_INACTIVE_SCALE,
        prev_scale.y * HUD_INACTIVE_SCALE};
    sfFloatRect inactive_bounds;
    float offset;

    sfSprite_setScale(w->ui_sprite, small_scale);
    inactive_bounds = sfSprite_getGlobalBounds(w->ui_sprite);
    offset = layout->bounds.width / 2.0F + HUD_ICON_GAP * layout->scale
        + inactive_bounds.width / 2.0F;
    sfSprite_setPosition(w->ui_sprite, (sfVector2f) {layout->pos.x - offset,
            layout->pos.y});
    sfRenderWindow_drawSprite(engine->window, w->ui_sprite, nullptr);
    sfSprite_setScale(w->ui_sprite, prev_scale);
}
// clang-format on

void draw_weapon_hud(engine_t *engine, game_data_t *d)
{
    hud_layout_t layout;

    get_layout(engine, &d->weapons[d->active_weapon], &layout);
    draw_cursor(engine, d->hud);
    draw_active_weapon_hud(engine, d, &layout);
    draw_inactive_weapon_hud(engine, d, &layout);
}
