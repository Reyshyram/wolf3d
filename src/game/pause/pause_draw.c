/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_draw
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

void draw_btn(engine_t *engine, ui_button_t *button)
{
    sfRenderWindow_drawRectangleShape(engine->window, button->background, NULL);
    if (button->text && sfText_getString(button->text))
        sfRenderWindow_drawText(engine->window, button->text, NULL);
}

void pause_draw(engine_t *engine, game_data_t *data)
{
    sfRenderWindow_drawSprite(engine->window, data->pause.bg, NULL);
    sfRenderWindow_drawRectangleShape(engine->window, data->pause.separator,
        NULL);
    draw_btn(engine, data->pause.resume);
    draw_btn(engine, data->pause.save);
    draw_btn(engine, data->pause.exit);
    draw_btn(engine, data->pause.controls);
    draw_btn(engine, data->pause.sounds);
    draw_btn(engine, data->pause.hud);
}
