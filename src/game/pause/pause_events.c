/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_events
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

void pause_events(engine_t *engine, game_data_t *data, sfEvent *event)
{
    ui_button_events(data->pause.resume, event, engine);
    ui_button_events(data->pause.save, event, engine);
    ui_button_events(data->pause.exit, event, engine);
    ui_button_events(data->pause.controls, event, engine);
    ui_button_events(data->pause.sounds, event, engine);
    ui_button_events(data->pause.hud, event, engine);
}
