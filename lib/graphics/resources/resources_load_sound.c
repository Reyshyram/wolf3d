/*
** EPITECH PROJECT, 2025
** resources_load_sound
** File description:
** Load a sound in the resources
*/

#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <SFML/Audio/Types.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/resources.h"

static void set_values(sound_resource_t *sound_resource, const char *path,
    sfSound *sound, sfSoundBuffer *buffer)
{
    sound_resource->path = strdup(path);
    sound_resource->sound = sound;
    sound_resource->buffer = buffer;
}

sfSound *resources_load_sound(resources_t *resources, const char *path)
{
    sfSound *sound = nullptr;
    sfSoundBuffer *buffer = nullptr;
    sound_resource_t *sound_resource;

    for (sound_resource_t *s = resources->sound_list; s; s = s->next)
        if (strcmp(s->path, path) == 0)
            return s->sound;
    buffer = sfSoundBuffer_createFromFile(path);
    if (!buffer)
        return nullptr;
    sound_resource = malloc(sizeof(*sound_resource));
    if (!sound_resource)
        return nullptr;
    sound = sfSound_create();
    sfSound_setBuffer(sound, buffer);
    set_values(sound_resource, path, sound, buffer);
    sound_resource->next = resources->sound_list;
    resources->sound_list = sound_resource;
    return sound;
}
