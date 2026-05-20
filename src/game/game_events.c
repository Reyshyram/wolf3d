/*
** EPITECH PROJECT, 2026
** game_events.c
** File description:
** Handle events during the game
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/View.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>

#include "graphics/engine.h"

#include "game.h"
#include "wolf3d.h"

static void switch_fullscreen(engine_t *engine)
{
    bool activate_fullscreen = !engine->is_fullscreen;
    sfVideoMode video_mode;

    if (activate_fullscreen)
        engine->windowed_size = engine->window_size;
    video_mode = activate_fullscreen
        ? sfVideoMode_getDesktopMode()
        : (sfVideoMode) {engine->windowed_size.x, engine->windowed_size.y, 32};
    sfRenderWindow_destroy(engine->window);
    engine->window = sfRenderWindow_create(video_mode, WIN_TITLE,
        activate_fullscreen ? sfFullscreen : (sfClose | sfResize), NULL);
    engine->is_fullscreen = activate_fullscreen;
    engine->window_size = (sfVector2u) {video_mode.width, video_mode.height};
    game_on_resize(engine);
    sfRenderWindow_setMouseCursorVisible(engine->window, false);
}

void game_event(engine_t *engine, sfEvent *event)
{
    game_data_t *data = (game_data_t *) engine->scene->data;

    if (!data || !event)
        return;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
        sfRenderWindow_close(engine->window);
    if (event->type == sfEvtMouseButtonPressed
        && event->mouseButton.button == sfMouseRight)
        data->player.is_zooming = true;
    if (event->type == sfEvtMouseButtonReleased
        && event->mouseButton.button == sfMouseRight)
        data->player.is_zooming = false;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyF)
        switch_fullscreen(engine);
}
