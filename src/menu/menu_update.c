/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** menu_update
*/

#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/sprite_anim.h"
#include "menu.h"
#include "wolf3d.h"
#include <stdlib.h>

void menu_update(engine_t *engine)
{
    menu_data_t *data = engine->scene->data;

    ui_button_update(engine, data->play_btn);
    ui_button_update(engine, data->exit_btn);
    sprite_anim_update(data->logo, engine->dt);
}
