/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_destroy
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

void pause_destroy(game_data_t *data)
{
    sfSprite_destroy(data->pause.bg);
    sfRectangleShape_destroy(data->pause.separator);
    ui_button_destroy(data->pause.resume);
    ui_button_destroy(data->pause.save);
    ui_button_destroy(data->pause.exit);
    ui_button_destroy(data->pause.controls);
    ui_button_destroy(data->pause.sounds);
    ui_button_destroy(data->pause.hud);
}
