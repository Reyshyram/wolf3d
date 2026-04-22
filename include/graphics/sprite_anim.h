/*
** EPITECH PROJECT, 2025
** sprite_anim.h
** File description:
** Header for sprite animations
*/

#ifndef SPRITE_ANIM_H
// clang-format off
    #define SPRITE_ANIM_H

    #include <SFML/Graphics/Rect.h>
    #include <SFML/Graphics/Types.h>
    #include <stddef.h>
    #include <stdint.h>

    #include "graphics/engine.h"
// clang-format on

typedef struct sprite_frame_info sprite_frame_info_t;
typedef struct sprite_anim sprite_anim_t;

struct sprite_frame_info {
    sfIntRect frame_rect;
    uint8_t nb_frames;
    float fps;
};

struct sprite_anim {
    sfSprite *sprite;
    sfTexture *texture;
    sprite_frame_info_t frame_info;
    uint8_t current_frame;
    float timer;
};

sprite_anim_t *sprite_anim_create(const char *texture_path,
    const sprite_frame_info_t *frame_info, engine_t *engine);
void sprite_anim_destroy(sprite_anim_t *sprite);
void sprite_anim_update(sprite_anim_t *sprite, float dt);

#endif /* !SPRITE_ANIM_H */
