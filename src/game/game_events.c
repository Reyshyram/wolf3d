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

#include "game.h"
#include "graphics/engine.h"

void game_event(engine_t *engine, sfEvent *event)
{
    game_data_t *data = (game_data_t *) engine->scene->data;

    if (!data || !event)
        return;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
        sfRenderWindow_close(engine->window);
    if (event->type == sfEvtMouseButtonPressed
        && event->mouseButton.button == sfMouseRight) {
        data->player.is_zooming = true;
        sfView_zoom(data->camera, 1.0F / ZOOM_FACTOR);
    }
    if (event->type == sfEvtMouseButtonReleased
        && event->mouseButton.button == sfMouseRight) {
        data->player.is_zooming = false;
        sfView_zoom(data->camera, ZOOM_FACTOR);
    }
}
