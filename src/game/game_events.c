/*
** EPITECH PROJECT, 2026
** game_events.c
** File description:
** Handle events during the game
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>

#include "graphics/engine.h"

#include "game.h"

void game_event(engine_t *engine, sfEvent *event)
{
    game_data_t *data = (game_data_t *) engine->scene->data;

    if (!data || !event)
        return;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
        sfRenderWindow_close(engine->window);
}
