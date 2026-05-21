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

static void check_pause_page_main(engine_t *engine, game_data_t *data)
{
    if (data->pause.page == PAUSE_PAGE_MAIN) {
        draw_btn(engine, data->pause.resume);
        draw_btn(engine, data->pause.save);
        draw_btn(engine, data->pause.exit);
        draw_btn(engine, data->pause.controls);
        draw_btn(engine, data->pause.sounds);
        draw_btn(engine, data->pause.hud);
    }
}

static void check_pause_page_controls(engine_t *engine, game_data_t *data)
{
    if (data->pause.page == PAUSE_PAGE_CONTROLS) {
        draw_btn(engine, data->pause.back);
        draw_btn(engine, data->pause.controls_move);
        draw_btn(engine, data->pause.controls_camera);
        draw_btn(engine, data->pause.controls_pause);
    }
}

static void check_pause_page_sounds(engine_t *engine, game_data_t *data)
{
    if (data->pause.page == PAUSE_PAGE_SOUNDS) {
        draw_btn(engine, data->pause.back);
        draw_btn(engine, data->pause.sound_master);
        draw_btn(engine, data->pause.sound_steps);
    }
}

static void check_pause_page_hud(engine_t *engine, game_data_t *data)
{
    if (data->pause.page == PAUSE_PAGE_HUD) {
        draw_btn(engine, data->pause.back);
        draw_btn(engine, data->pause.hud_minimap);
        draw_btn(engine, data->pause.hud_timer);
    }
}

void pause_draw(engine_t *engine, game_data_t *data)
{
    sfRenderWindow_drawSprite(engine->window, data->pause.bg, NULL);
    sfRenderWindow_drawRectangleShape(engine->window, data->pause.separator,
        NULL);
    check_pause_page_main(engine, data);
    check_pause_page_controls(engine, data);
    check_pause_page_sounds(engine, data);
    check_pause_page_hud(engine, data);
}
