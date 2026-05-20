/*
** EPITECH PROJECT, 2026
** game_events.c
** File description:
** Handle events during the game
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>

#include "graphics/engine.h"

#include "game.h"
#include "weapons.h"

static void weapons_events(game_data_t *d, sfEvent *event)
{
    weapon_t *w = &d->weapons[d->active_weapon];

    if (event->type == sfEvtMouseButtonPressed
        && event->mouseButton.button == sfMouseLeft
        && !w->weapon_data->is_auto)
        weapon_shoot(d);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyR)
        weapon_reload(d);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyTab)
        weapon_change(d);
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
    weapons_events(data, event);
}
