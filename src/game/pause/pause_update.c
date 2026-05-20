/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_update
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

void pause_update(engine_t *engine, game_data_t *data)
{
    ui_button_update(engine, data->pause.resume);
    ui_button_update(engine, data->pause.save);
    ui_button_update(engine, data->pause.exit);
    ui_button_update(engine, data->pause.controls);
    ui_button_update(engine, data->pause.sounds);
    ui_button_update(engine, data->pause.hud);
}
