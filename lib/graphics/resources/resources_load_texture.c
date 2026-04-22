/*
** EPITECH PROJECT, 2025
** resources_load_texture
** File description:
** Load a texture in the resources
*/

#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/resources.h"

sfTexture *resources_load_texture(resources_t *resources, const char *path)
{
    sfTexture *texture = nullptr;
    texture_resource_t *texture_resource;

    for (texture_resource_t *curr_texture = resources->textures_list;
        curr_texture; curr_texture = curr_texture->next)
        if (strcmp(curr_texture->path, path) == 0)
            return curr_texture->texture;
    texture = sfTexture_createFromFile(path, nullptr);
    if (!texture) {
        fprintf(stderr, "Failed to load texture: %s\n", path);
        return nullptr;
    }
    texture_resource = malloc(sizeof(*texture_resource));
    if (!texture_resource)
        return nullptr;
    texture_resource->path = strdup(path);
    texture_resource->texture = texture;
    texture_resource->next = resources->textures_list;
    resources->textures_list = texture_resource;
    return texture;
}
