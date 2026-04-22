/*
** EPITECH PROJECT, 2025
** sprite_anim_destroy.c
** File description:
** Destroy an animated sprite struct
*/

#include <SFML/Graphics/Sprite.h>
#include <stdlib.h>

#include "graphics/sprite_anim.h"

void sprite_anim_destroy(sprite_anim_t *sprite)
{
    if (!sprite)
        return;
    if (sprite->sprite)
        sfSprite_destroy(sprite->sprite);
    free(sprite);
}
