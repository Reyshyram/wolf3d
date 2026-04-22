/*
** EPITECH PROJECT, 2025
** sprite_anim_create.c
** File description:
** Create an animated sprite struct
*/

#include <SFML/Config.h>
#include <SFML/Graphics/Sprite.h>
#include <stdlib.h>

#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/sprite_anim.h"

sprite_anim_t *sprite_anim_create(const char *texture_path,
    const sprite_frame_info_t *frame_info, engine_t *engine)
{
    sprite_anim_t *sprite = malloc(sizeof(*sprite));

    if (!sprite)
        return nullptr;
    sprite->texture = resources_load_texture(engine->resources, texture_path);
    if (!sprite->texture) {
        free(sprite);
        return nullptr;
    }
    sprite->sprite = sfSprite_create();
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    sprite->frame_info = *frame_info;
    sprite->current_frame = 0;
    sprite->timer = 0;
    sfSprite_setTextureRect(sprite->sprite, sprite->frame_info.frame_rect);
    return sprite;
}
