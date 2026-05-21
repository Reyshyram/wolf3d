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

void set_pause_page(engine_t *engine, pause_page_t page)
{
    game_data_t *data = engine->scene->data;

    if (!data)
        return;
    data->pause.page = page;
}

void set_button_state(ui_button_t *button, const char *label,
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

void pause_on_back(void *data)
{
    engine_t *engine = data;

    set_pause_page(engine, PAUSE_PAGE_MAIN);
}
