/*
** EPITECH PROJECT, 2025
** resources.h
** File description:
** Header file for the game engine resources
*/

#ifndef ENGINE_RESOURCES_H
// clang-format off
    #define ENGINE_RESOURCES_H

    #include <SFML/Audio/Types.h>
    #include <SFML/Graphics/Types.h>
// clang-format on

typedef struct engine engine_t;
typedef struct font_resource font_resource_t;
typedef struct texture_resource texture_resource_t;
typedef struct music_resource music_resource_t;
typedef struct sound_resource sound_resource_t;
typedef struct resources resources_t;

struct texture_resource {
    char *path;
    sfTexture *texture;
    struct texture_resource *next;
};

struct font_resource {
    char *path;
    sfFont *font;
    struct font_resource *next;
};

struct music_resource {
    char *path;
    sfMusic *music;
    struct music_resource *next;
};

struct sound_resource {
    char *path;
    sfSound *sound;
    sfSoundBuffer *buffer;
    struct sound_resource *next;
};

struct resources {
    font_resource_t *fonts_list;
    texture_resource_t *textures_list;
    music_resource_t *music_list;
    sound_resource_t *sound_list;
};

sfFont *resources_load_font(resources_t *resources, const char *path);
sfTexture *resources_load_texture(resources_t *resources, const char *path);
sfMusic *resources_load_music(resources_t *resources, const char *path);
sfSound *resources_load_sound(resources_t *resources, const char *path);
void resources_destroy(resources_t *resources);

#endif /* !ENGINE_RESOURCES_H */
