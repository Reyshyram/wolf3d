/*
** EPITECH PROJECT, 2026
** weapon_actions.c
** File description:
** actions for weapons
*/

#include <SFML/Audio/Sound.h>

#include "game.h"
#include "weapons.h"

bool weapon_shoot(game_data_t *d)
{
    weapon_t *w = &d->weapons[d->active_weapon];

    if (w->is_reloading || w->shoot_cooldown > 0 || w->ammo <= 0)
        return false;
    w->ammo--;
    w->shoot_cooldown = w->weapon_data->fire_cooldown;
    d->recoil_vel -= w->weapon_data->recoil;
    w->shoot_anim_timer = SHOOT_ANIM_DURATION;
    sfSound_play(w->shoot_sound);
    return true;
}

void weapon_reload(game_data_t *d)
{
    weapon_t *w = &d->weapons[d->active_weapon];

    if (w->is_reloading || w->ammo >= w->weapon_data->max_ammo
        || w->type == WEAPON_GRENADE)
        return;
    w->is_reloading = true;
    w->reload_timer = 0;
    sfSound_play(w->reload_sound);
}

void weapon_change(game_data_t *d)
{
    d->active_weapon = (d->active_weapon == WEAPON_SLOT_MAIN)
        ? WEAPON_SLOT_GRENADE
        : WEAPON_SLOT_MAIN;
}
