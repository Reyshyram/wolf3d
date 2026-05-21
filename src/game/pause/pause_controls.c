/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_controls
*/

#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/Color.h>
#include <stdio.h>

#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

void pause_on_controls(void *data)
{
    engine_t *engine = data;

    set_pause_page(engine, PAUSE_PAGE_CONTROLS);
}

void pause_on_controls_keys(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data)
        return;
    game_data->is_fr = !game_data->is_fr;
    if (!game_data->is_fr) {
        sfRectangleShape_setTexture(game_data->pause.controls_move->background,
            resources_load_texture(engine->resources,
                "assets/sprites/main_menu/button_en.png"), sfTrue);
    } else {
        sfRectangleShape_setTexture(game_data->pause.controls_move->background,
            resources_load_texture(engine->resources,
                "assets/sprites/main_menu/button_fr.png"), sfTrue);
    }
}

void pause_on_controls_resize(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data)
        return;
    switch_fullscreen(engine);
    if (engine->is_fullscreen) {
        sfRenderWindow_setMouseCursorVisible(engine->window, true);
        sfRenderWindow_setMouseCursorGrabbed(engine->window, false);
    }
}
