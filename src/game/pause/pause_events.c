/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_events
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

static void handle_main_events(engine_t *engine, game_data_t *data,
    sfEvent *event)
{
    ui_button_events(data->pause.resume, event, engine);
    ui_button_events(data->pause.save, event, engine);
    ui_button_events(data->pause.exit, event, engine);
    ui_button_events(data->pause.controls, event, engine);
    ui_button_events(data->pause.sounds, event, engine);
    ui_button_events(data->pause.hud, event, engine);
}

static void handle_controls_events(engine_t *engine, game_data_t *data,
    sfEvent *event)
{
    ui_button_events(data->pause.back, event, engine);
}

static void handle_sounds_events(engine_t *engine, game_data_t *data,
    sfEvent *event)
{
    ui_button_events(data->pause.back, event, engine);
    ui_button_events(data->pause.sound_master, event, engine);
    ui_button_events(data->pause.sound_steps, event, engine);
}

static void handle_hud_events(engine_t *engine, game_data_t *data,
    sfEvent *event)
{
    ui_button_events(data->pause.back, event, engine);
    ui_button_events(data->pause.hud_minimap, event, engine);
    ui_button_events(data->pause.hud_timer, event, engine);
}

void pause_events(engine_t *engine, game_data_t *data, sfEvent *event)
{
    if (!data || !event)
        return;
    if (data->pause.page == PAUSE_PAGE_MAIN)
        handle_main_events(engine, data, event);
    if (data->pause.page == PAUSE_PAGE_CONTROLS)
        handle_controls_events(engine, data, event);
    if (data->pause.page == PAUSE_PAGE_SOUNDS)
        handle_sounds_events(engine, data, event);
    if (data->pause.page == PAUSE_PAGE_HUD)
        handle_hud_events(engine, data, event);
}
