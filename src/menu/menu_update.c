/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** menu_update
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "menu.h"
#include "wolf3d.h"

void menu_update(engine_t *engine)
{
    menu_data_t *data = engine->scene->data;

    ui_button_update(engine, data->play_btn);
    ui_button_update(engine, data->exit_btn);
}
