/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_hud
*/

#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/Color.h>
#include <stdio.h>

#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

void pause_on_hud(void *data)
{
    engine_t *engine = data;

    set_pause_page(engine, PAUSE_PAGE_HUD);
}

void pause_on_hud_minimap(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data || !game_data->hud)
        return;
    if (game_data->hud->show_minimap == true) {
        sfRectangleShape_setTexture(game_data->pause.hud_minimap->background,
            resources_load_texture(engine->resources,
                "assets/sprites/main_menu/button_map_ko.png"), sfTrue);
    } else {
        sfRectangleShape_setTexture(game_data->pause.hud_minimap->background,
            resources_load_texture(engine->resources,
                "assets/sprites/main_menu/button_map_ok.png"), sfTrue);
    }
    game_data->hud->show_minimap = !game_data->hud->show_minimap;
}

void pause_on_hud_timer(void *data)
{
    engine_t *engine = data;
    game_data_t *game_data = engine->scene->data;

    if (!game_data || !game_data->hud)
        return;
    if (game_data->hud->show_timer == true) {
        sfRectangleShape_setTexture(game_data->pause.hud_timer->background,
            resources_load_texture(engine->resources,
                "assets/sprites/main_menu/button_time_ko.png"), sfTrue);
    } else {
        sfRectangleShape_setTexture(game_data->pause.hud_timer->background,
            resources_load_texture(engine->resources,
                "assets/sprites/main_menu/button_time_ok.png"), sfTrue);
    }
    game_data->hud->show_timer = !game_data->hud->show_timer;
}
