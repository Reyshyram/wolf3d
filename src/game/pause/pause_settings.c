/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_settings
*/

#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/Color.h>
#include <stdio.h>

#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

static void set_pause_page(engine_t *engine, pause_page_t page)
{
    game_data_t *data = engine->scene->data;

    if (!data)
        return;
    data->pause.page = page;
}

static void set_button_state(ui_button_t *button, const char *label,
    bool enabled)
{
    char text[32];
    sfColor color = enabled ? sfGreen : sfRed;

    snprintf(text, sizeof(text), "%s: %s", label, enabled ? "ON" : "OFF");
    ui_button_set_text(button, text, 18, &color);
}

void pause_on_controls(void *data)
{
    engine_t *engine = data;

    set_pause_page(engine, PAUSE_PAGE_CONTROLS);
}

void pause_on_sounds(void *data)
{
    engine_t *engine = data;

    set_pause_page(engine, PAUSE_PAGE_SOUNDS);
}

void pause_on_hud(void *data)
{
    engine_t *engine = data;

    set_pause_page(engine, PAUSE_PAGE_HUD);
}

void pause_on_back(void *data)
{
    engine_t *engine = data;

    set_pause_page(engine, PAUSE_PAGE_MAIN);
}

void pause_on_sound_master(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data)
        return;
    game_data->sounds_enabled = !game_data->sounds_enabled;
    if (!game_data->sounds_enabled)
        sfSound_pause(game_data->player.steps);
    set_button_state(game_data->pause.sound_master, "Master",
        game_data->sounds_enabled);
    set_button_state(game_data->pause.sound_steps, "Pas",
        game_data->sounds_enabled);
}

void pause_on_sound_steps(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data)
        return;
    game_data->sounds_enabled = !game_data->sounds_enabled;
    if (!game_data->sounds_enabled)
        sfSound_pause(game_data->player.steps);
    set_button_state(game_data->pause.sound_master, "Master",
        game_data->sounds_enabled);
    set_button_state(game_data->pause.sound_steps, "Pas",
        game_data->sounds_enabled);
}

void pause_on_hud_minimap(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data || !game_data->hud)
        return;
    game_data->hud->show_minimap = !game_data->hud->show_minimap;
    set_button_state(game_data->pause.hud_minimap, "Mini-map",
        game_data->hud->show_minimap);
}

void pause_on_hud_timer(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data || !game_data->hud)
        return;
    game_data->hud->show_timer = !game_data->hud->show_timer;
    set_button_state(game_data->pause.hud_timer, "Timer",
        game_data->hud->show_timer);
}
