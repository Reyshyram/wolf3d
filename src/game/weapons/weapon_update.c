/*
** EPITECH PROJECT, 2026
** weapon_update.c
** File description:
** Update the weapons
*/

#include <SFML/Window/Mouse.h>
#include <math.h>

#include "graphics/engine.h"

#include "game.h"
#include "weapons.h"
#include "wolf3d.h"

static void update_timers(weapon_t *w, float dt)
{
    w->shoot_cooldown -= dt;
    w->shoot_cooldown = fmaxf(w->shoot_cooldown, 0);
    w->shoot_anim_timer -= dt;
    w->shoot_anim_timer = fmaxf(w->shoot_anim_timer, 0);
    if (!w->is_reloading)
        return;
    w->reload_timer += dt;
    if (w->reload_timer >= w->weapon_data->reload_time) {
        w->ammo = w->weapon_data->max_ammo;
        w->is_reloading = false;
        w->reload_timer = 0;
    }
}

static void update_recoil(engine_t *engine, game_data_t *d, float dt)
{
    d->camera_height += d->recoil_vel * dt;
    d->recoil_vel *= (1.0F - RECOIL_SPEED * dt);
    if (d->camera_height > (float) engine->window_size.y / 2 - 1)
        d->camera_height = (float) engine->window_size.y / 2 - 1;
    if (d->camera_height < -(float) engine->window_size.y / 2 + 1)
        d->camera_height = -(float) engine->window_size.y / 2 + 1;
}

void update_weapons(engine_t *engine, game_data_t *d)
{
    weapon_t *w = &d->weapons[d->active_weapon];

    for (size_t i = 0; i < WEAPON_SLOT_COUNT; i++)
        update_timers(&d->weapons[i], engine->dt);
    update_recoil(engine, d, engine->dt);
    if (w->ammo == 0 && !w->is_reloading && w->type != WEAPON_GRENADE)
        weapon_reload(d);
    if (sfMouse_isButtonPressed(sfMouseLeft)
        && d->weapons[d->active_weapon].weapon_data->is_auto)
        weapon_shoot(d);
}
