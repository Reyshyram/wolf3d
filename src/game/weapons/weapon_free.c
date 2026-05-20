/*
** EPITECH PROJECT, 2026
** weapon_free.c
** File description:
** Free weapons
*/

#include <SFML/Graphics/Sprite.h>

#include "game.h"
#include "weapons.h"

static void free_weapon(weapon_t *w)
{
    if (w->ui_sprite)
        sfSprite_destroy(w->ui_sprite);
    if (w->held_sprite)
        sfSprite_destroy(w->held_sprite);
}

void free_weapons(game_data_t *data)
{
    for (size_t i = 0; i < WEAPON_SLOT_COUNT; i++)
        free_weapon(&data->weapons[i]);
}
