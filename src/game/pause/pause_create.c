/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_create
*/

#include "game.h"
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/ui.h"
#include "menu.h"
#include "wolf3d.h"

static void init_pause_bg(engine_t *engine, pause_menu_t *pause)
{
    sfTexture *texture = resources_load_texture(engine->resources,
        "assets/sprites/main_menu/bg_menu_pause.png");
    sfVector2u text_size = sfTexture_getSize(texture);
    sfColor line_c = {0, 0, 0, 100};

    pause->bg = sfSprite_create();
    sfSprite_setTexture(pause->bg, texture, sfTrue);
    sfSprite_setScale(pause->bg,
        (sfVector2f) {(float) engine->window_size.x / (float) text_size.x,
            (float) engine->window_size.y / (float) text_size.y});
    pause->separator = sfRectangleShape_create();
    sfRectangleShape_setSize(pause->separator, (sfVector2f) {4.0F, 500.0F});
    sfRectangleShape_setFillColor(pause->separator, line_c);
    sfRectangleShape_setOrigin(pause->separator, (sfVector2f) {2.0F, 250.0F});
    sfRectangleShape_setPosition(pause->separator, (sfVector2f)
        {engine->window_size.x / 2.0F, engine->window_size.y / 2.0F});
}

static void init_main_left(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f left = {engine->window_size.x / 2.0F - 250.0F,
        engine->window_size.y / 2.0F - 100.0F};

    pause->resume = create_btn(engine,
        "assets/sprites/main_menu/button_resume.png", &left);
    pause->resume->on_click = &pause_on_resume;
    pause->resume->data = engine;
    left.y += 100.0F;
    pause->save = create_btn(engine,
        "assets/sprites/main_menu/button_save.png", &left);
    pause->save->on_click = &pause_on_save;
    pause->save->data = engine;
    left.y += 100.0F;
    pause->exit = create_btn(engine,
        "assets/sprites/main_menu/button_exit.png", &left);
    pause->exit->on_click = &pause_on_exit;
    pause->exit->data = engine;
}

static void init_main_right(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f right = {engine->window_size.x / 2.0F + 250.0F,
        engine->window_size.y / 2.0F - 100.0F};

    pause->controls = create_btn(engine,
        "assets/sprites/main_menu/button_keys.png", &right);
    pause->controls->on_click = &pause_on_controls;
    pause->controls->data = engine;
    right.y += 100.0F;
    pause->sounds = create_btn(engine,
        "assets/sprites/main_menu/button_sounds.png", &right);
    pause->sounds->on_click = &pause_on_sounds;
    pause->sounds->data = engine;
    right.y += 100.0F;
    pause->hud = create_btn(engine,
        "assets/sprites/main_menu/button_params.png", &right);
    pause->hud->on_click = &pause_on_hud;
    pause->hud->data = engine;
}

static void init_controls_page(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f keys_pos = {engine->window_size.x / 4.0F,
        engine->window_size.y / 2.0F};
    sfVector2f zoom_pos = {(engine->window_size.x / 4.0F) * 3.F,
        engine->window_size.y / 2.0F};

    pause->controls_move = create_btn(engine,
        "assets/sprites/main_menu/button_fr.png", &keys_pos);
    pause->controls_move->on_click = &pause_on_controls_keys;
    pause->controls_move->data = engine;
    pause->win_mode = create_btn(engine,
        "assets/sprites/main_menu/button_resize.png", &zoom_pos);
    pause->win_mode->on_click = &pause_on_controls_resize;
    pause->win_mode->data = engine;
}

static void init_sounds_page(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f master_pos = {engine->window_size.x / 4.0F,
        engine->window_size.y / 2.0F};
    sfVector2f steps_pos = {(engine->window_size.x / 4.0F) * 3.F,
        engine->window_size.y / 2.0F};

    pause->sound_master = create_btn(engine,
        "assets/sprites/main_menu/button_master_vol.png", &master_pos);
    pause->sound_master->on_click = &pause_on_sound_master;
    pause->sound_master->data = engine;
    pause->sound_steps = create_btn(engine,
        "assets/sprites/main_menu/button_steps_vol.png", &steps_pos);
    pause->sound_steps->on_click = &pause_on_sound_steps;
    pause->sound_steps->data = engine;
}

static void init_hud_page(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f map_pos = {engine->window_size.x / 4.0F,
        engine->window_size.y / 2.0F};
    sfVector2f time_pos = {(engine->window_size.x / 4.0F) * 3.F,
        engine->window_size.y / 2.0F};

    pause->hud_minimap = create_btn(engine,
        "assets/sprites/main_menu/button_map_ok.png", &map_pos);
    pause->hud_minimap->on_click = &pause_on_hud_minimap;
    pause->hud_minimap->data = engine;
    pause->hud_timer = create_btn(engine,
        "assets/sprites/main_menu/button_time_ok.png", &time_pos);
    pause->hud_timer->on_click = &pause_on_hud_timer;
    pause->hud_timer->data = engine;
}

void pause_init(engine_t *engine, game_data_t *data)
{
    init_pause_bg(engine, &data->pause);
    init_main_left(engine, &data->pause);
    init_main_right(engine, &data->pause);
    init_controls_page(engine, &data->pause);
    init_sounds_page(engine, &data->pause);
    init_hud_page(engine, &data->pause);
    data->pause.page = PAUSE_PAGE_MAIN;
}
