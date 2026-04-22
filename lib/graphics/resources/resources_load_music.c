/*
** EPITECH PROJECT, 2025
** resources_load_music
** File description:
** Load a music in the resources
*/

#include <SFML/Audio/Music.h>
#include <SFML/Audio/Types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/resources.h"

sfMusic *resources_load_music(resources_t *resources, const char *path)
{
    sfMusic *music = nullptr;
    music_resource_t *music_resource;

    for (music_resource_t *curr_music = resources->music_list; curr_music;
        curr_music = curr_music->next)
        if (strcmp(curr_music->path, path) == 0)
            return curr_music->music;
    music = sfMusic_createFromFile(path);
    if (!music) {
        fprintf(stderr, "Failed to load music: %s\n", path);
        return nullptr;
    }
    music_resource = malloc(sizeof(*music_resource));
    if (!music_resource)
        return nullptr;
    music_resource->path = strdup(path);
    music_resource->music = music;
    music_resource->next = resources->music_list;
    resources->music_list = music_resource;
    return music;
}
