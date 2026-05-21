/*
** EPITECH PROJECT, 2025
** engine_init.c
** File description:
** Initialize the game engine
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/WindowBase.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/engine.h"
#include "graphics/resources.h"

// NOLINTBEGIN(readability-simplify-boolean-expr)
static bool engine_init_resources(engine_t *engine, sfVideoMode *video_mode)
{
    engine->clock = sfClock_create();
    if (!engine->clock)
        return false;
    engine->transition_rect = sfRectangleShape_create();
    if (!engine->transition_rect)
        return false;
    sfRectangleShape_setSize(engine->transition_rect,
        (sfVector2f) {(float) video_mode->width, (float) video_mode->height});
    engine->resources = malloc(sizeof(resources_t));
    if (!engine->resources)
        return false;
    memset(engine->resources, 0, sizeof(*engine->resources));
    engine->default_font =
        resources_load_font(engine->resources, DEFAULT_FONT);
    if (!engine->default_font)
        return false;
    return true;
}
// NOLINTEND(readability-simplify-boolean-expr)

bool engine_init(engine_t *engine, const char *title, sfVideoMode *video_mode,
    bool is_fullscreen)
{
    if (!engine)
        return false;
    memset(engine, 0, sizeof(*engine));
    engine->is_fullscreen = is_fullscreen;
    engine->windowed_size =
        (sfVector2u) {video_mode->width, video_mode->height};
    engine->window = sfRenderWindow_create(*video_mode, title,
        sfClose | sfResize | (is_fullscreen ? sfFullscreen : 0), nullptr);
    if (!engine->window)
        return false;
    engine->window_size = (sfVector2u) {video_mode->width, video_mode->height};
    return engine_init_resources(engine, video_mode);
}
