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

#include "menu.h"
#include "game.h"
#include "graphics/engine.h"

static void handle_escape(engine_t *engine, game_data_t *data)
{
    if (data->is_paused && data->pause.page != PAUSE_PAGE_MAIN) {
        data->pause.page = PAUSE_PAGE_MAIN;
        return;
    }
    data->is_paused = !data->is_paused;
    sfRenderWindow_setMouseCursorVisible(engine->window, data->is_paused);
    sfRenderWindow_setMouseCursorGrabbed(engine->window, !data->is_paused);
}

void game_event(engine_t *engine, sfEvent *event)
{
    game_data_t *data = (game_data_t *) engine->scene->data;

    if (!data || !event)
        return;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
        handle_escape(engine, data);
    if (data->is_paused) {
        pause_events(engine, data, event);
        return;
    }
    if (event->type == sfEvtMouseButtonPressed
        && event->mouseButton.button == sfMouseRight)
        data->player.is_zooming = true;
    if (event->type == sfEvtMouseButtonReleased
        && event->mouseButton.button == sfMouseRight)
        data->player.is_zooming = false;
}
