/*
** EPITECH PROJECT, 2026
** weapon_draw.c
** File description:
** Draw the weapon
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>
#include <math.h>

#include "graphics/engine.h"
#include "graphics/maths.h"

#include "game.h"
#include "weapons.h"
#include "wolf3d.h"

static sfVector2f get_shoot_offset(weapon_t *w)
{
    float offset =
        sinf(w->shoot_anim_timer / SHOOT_ANIM_DURATION * (float) M_PI);

    return (sfVector2f) {offset * SHOOT_OFFSET_X, offset * SHOOT_OFFSET_Y};
}

static float get_reload_offset(engine_t *engine, weapon_t *w)
{
    if (!w->is_reloading)
        return 0;
    if (w->reload_timer < RELOAD_ANIM_TIME)
        return (w->reload_timer / RELOAD_ANIM_TIME)
            * (float) engine->window_size.y / 2;
    if (w->reload_timer > w->weapon_data->reload_time - RELOAD_ANIM_TIME)
        return (w->weapon_data->reload_time - w->reload_timer)
            / RELOAD_ANIM_TIME * (float) engine->window_size.y / 2;
    return (float) engine->window_size.y / 2;
}

static sfVector2f get_held_pos(engine_t *engine, weapon_t *w)
{
    sfVector2f offset = get_shoot_offset(w);
    float reload_offset = get_reload_offset(engine, w);

    return (sfVector2f) {WEAPON_POS_X + offset.x,
        WEAPON_POS_Y + offset.y + reload_offset};
}

void draw_weapon(engine_t *engine, game_data_t *d)
{
    weapon_t *w = &d->weapons[d->active_weapon];
    sfVector2f pos = get_held_pos(engine, w);

    sfSprite_setPosition(w->held_sprite, pos);
    sfRenderWindow_drawSprite(engine->window, w->held_sprite, nullptr);
}
