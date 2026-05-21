/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_sounds
*/

#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/Color.h>
#include <stdio.h>

#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

void pause_on_sounds(void *data)
{
    engine_t *engine = data;

    set_pause_page(engine, PAUSE_PAGE_SOUNDS);
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
}

void pause_on_sound_steps(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data)
        return;
    if (!game_data->sounds_enabled) {
        game_data->sounds_enabled = !game_data->sounds_enabled;
        sfSound_play(game_data->player.steps);
    } else {
        sfSound_pause(game_data->player.steps);
    }
}
