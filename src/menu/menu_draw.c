/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** menu_draw
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "menu.h"
#include "wolf3d.h"

void menu_draw(engine_t *engine)
{
    menu_data_t *data = engine->scene->data;

    sfRenderWindow_drawSprite(engine->window, data->bg, NULL);
    sfRenderWindow_drawSprite(engine->window, data->logo, NULL);
}
