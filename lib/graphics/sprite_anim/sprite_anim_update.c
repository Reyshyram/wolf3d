/*
** EPITECH PROJECT, 2025
** sprite_anim_update.c
** File description:
** Update an animated sprite struct
*/

#include <SFML/Graphics/Sprite.h>

#include "graphics/sprite_anim.h"

void sprite_anim_update(sprite_anim_t *sprite, float dt)
{
    float frame_duration = 0;

    if (!sprite)
        return;
    frame_duration = (float) 1 / sprite->frame_info.fps;
    sprite->timer += dt;
    while (sprite->timer >= frame_duration) {
        sprite->timer -= frame_duration;
        sprite->current_frame++;
        sprite->current_frame %= sprite->frame_info.nb_frames;
        sprite->frame_info.frame_rect.left =
            sprite->frame_info.frame_rect.width * (int) sprite->current_frame;
        sfSprite_setTextureRect(sprite->sprite, sprite->frame_info.frame_rect);
    }
}
