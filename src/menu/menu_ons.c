/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** menu_ons
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "game.h"
#include "menu.h"
#include "wolf3d.h"

void on_play_click(void *data)
{
    engine_t *engine = data;

    sfRenderWindow_setMouseCursorGrabbed(engine->window, sfTrue);
    sfRenderWindow_setMouseCursorVisible(engine->window, sfFalse);
    engine_set_scene(engine, game_create(), true);
}

void on_exit_click(void *data)
{
    engine_t *engine = data;

    sfRenderWindow_close(engine->window);
}

void menu_on_enter(engine_t *engine)
{
    menu_data_t *data = engine->scene->data;

    init_sprites(engine, data);
    init_buttons(engine, data);
    sfRenderWindow_setMouseCursorVisible(engine->window, sfTrue);
    sfRenderWindow_setMouseCursorGrabbed(engine->window, sfFalse);
}

void menu_on_exit(engine_t *engine)
{
    menu_data_t *data = engine->scene->data;

    sfSprite_destroy(data->bg);
    sfSprite_destroy(data->logo);
    ui_button_destroy(data->play_btn);
    ui_button_destroy(data->exit_btn);
    free(data);
}
