/*
** EPITECH PROJECT, 2025
** resources_load_font
** File description:
** Load a font in the resources
*/

#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/resources.h"

sfFont *resources_load_font(resources_t *resources, const char *path)
{
    sfFont *font = nullptr;
    font_resource_t *font_resource;

    for (font_resource_t *curr_font = resources->fonts_list; curr_font;
        curr_font = curr_font->next)
        if (strcmp(curr_font->path, path) == 0)
            return curr_font->font;
    font = sfFont_createFromFile(path);
    if (!font) {
        fprintf(stderr, "Failed to load font: %s\n", path);
        return nullptr;
    }
    font_resource = malloc(sizeof(*font_resource));
    if (!font_resource)
        return nullptr;
    font_resource->path = strdup(path);
    font_resource->font = font;
    font_resource->next = resources->fonts_list;
    resources->fonts_list = font_resource;
    return font;
}
