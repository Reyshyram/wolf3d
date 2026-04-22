/*
** EPITECH PROJECT, 2025
** engine_set_cursor.c
** File description:
** Set the cursor for the game engine
*/

#include <SFML/Config.h>
#include <SFML/Graphics/Image.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Cursor.h>
#include <stdio.h>

#include "graphics/engine.h"

void engine_set_cursor(engine_t *engine, const char *path,
    bool set_origin_to_middle)
{
    sfImage *cursor_image = sfImage_createFromFile(path);
    const sfUint8 *pixels;
    sfVector2u hotspot = {0, 0};

    if (!cursor_image) {
        fprintf(stderr, "Failed to load cursor: %s\n", path);
        return;
    }
    pixels = sfImage_getPixelsPtr(cursor_image);
    if (set_origin_to_middle) {
        hotspot = sfImage_getSize(cursor_image);
        hotspot.x /= 2;
        hotspot.y /= 2;
    }
    engine->cursor = sfCursor_createFromPixels(pixels,
        sfImage_getSize(cursor_image), hotspot);
    sfRenderWindow_setMouseCursor(engine->window, engine->cursor);
    sfImage_destroy(cursor_image);
}
