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
