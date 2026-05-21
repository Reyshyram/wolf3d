/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** menu_loop
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "menu.h"
#include "wolf3d.h"

void handle_menu_events(engine_t *engine, sfEvent *event)
{
    menu_data_t *data = engine->scene->data;

    ui_button_events(data->play_btn, event, engine);
    ui_button_events(data->exit_btn, event, engine);
}
