/*
** EPITECH PROJECT, 2025
** engine_destroy.c
** File description:
** Free the memory used by the engine
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Clock.h>
#include <SFML/Window/Cursor.h>
#include <stdlib.h>

#include "graphics/engine.h"
#include "graphics/resources.h"

void engine_destroy(engine_t *engine)
{
    if (!engine)
        return;
    if (engine->scene && engine->scene->on_exit)
        engine->scene->on_exit(engine);
    free(engine->scene);
    if (engine->clock)
        sfClock_destroy(engine->clock);
    if (engine->window)
        sfRenderWindow_destroy(engine->window);
    if (engine->cursor)
        sfCursor_destroy(engine->cursor);
    if (engine->resources) {
        resources_destroy(engine->resources);
        free(engine->resources);
    }
    if (engine->transition_rect)
        sfRectangleShape_destroy(engine->transition_rect);
}
