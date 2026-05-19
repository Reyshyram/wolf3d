/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** menu_clicks
*/

#include <stdlib.h>

#include "graphics/engine.h"
#include "graphics/ui.h"
#include "graphics/resources.h"

#include "game.h"

void on_play_click(void *data)
{
    engine_t *engine = data;

    engine_set_scene(engine, game_create(), true);
}

void on_exit_click(void *data)
{
    engine_t *engine = data;

    sfRenderWindow_close(engine->window);
}
