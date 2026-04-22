/*
** EPITECH PROJECT, 2025
** resources_destroy.c
** File description:
** Cleanup the resources
*/

#include <SFML/Audio/Music.h>
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Texture.h>
#include <stdlib.h>

#include "graphics/resources.h"

static void destroy_textures(resources_t *resources)
{
    texture_resource_t *texture_resource = nullptr;

    while (resources->textures_list) {
        texture_resource = resources->textures_list->next;
        sfTexture_destroy(resources->textures_list->texture);
        free(resources->textures_list->path);
        free(resources->textures_list);
        resources->textures_list = texture_resource;
    }
}

static void destroy_fonts(resources_t *resources)
{
    font_resource_t *font_resource = nullptr;

    while (resources->fonts_list) {
        font_resource = resources->fonts_list->next;
        sfFont_destroy(resources->fonts_list->font);
        free(resources->fonts_list->path);
        free(resources->fonts_list);
        resources->fonts_list = font_resource;
    }
}

static void destroy_musics(resources_t *resources)
{
    music_resource_t *music_resource = nullptr;

    while (resources->music_list) {
        music_resource = resources->music_list->next;
        sfMusic_destroy(resources->music_list->music);
        free(resources->music_list->path);
        free(resources->music_list);
        resources->music_list = music_resource;
    }
}

static void destroy_sounds(resources_t *resources)
{
    sound_resource_t *sound_resource = nullptr;

    while (resources->sound_list) {
        sound_resource = resources->sound_list->next;
        sfSound_destroy(resources->sound_list->sound);
        sfSoundBuffer_destroy(resources->sound_list->buffer);
        free(resources->sound_list->path);
        free(resources->sound_list);
        resources->sound_list = sound_resource;
    }
}

void resources_destroy(resources_t *resources)
{
    destroy_textures(resources);
    destroy_fonts(resources);
    destroy_musics(resources);
    destroy_sounds(resources);
}
