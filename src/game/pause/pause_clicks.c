/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_clicks
*/

#include <stdio.h>
#include "graphics/engine.h"
#include "game.h"
#include "menu.h"

void pause_on_resume(void *data)
{
    engine_t *engine = data;
    game_data_t *data = engine->scene->data;

    data->is_paused = false;
    sfRenderWindow_setMouseCursorVisible(engine->window, sfFalse);
    sfRenderWindow_setMouseCursorGrabbed(engine->window, sfTrue);
}

void pause_on_save(void *data)
{
    (void)data;
    puts("Save clicked");
}

void pause_on_exit(void *data)
{
    engine_t *engine = data;

    engine_set_scene(engine, menu_create(), true);
}
