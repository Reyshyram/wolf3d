/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_create
*/

#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/ui.h"
#include "game.h"
#include "menu.h"
#include "wolf3d.h"

static ui_button_t *create_btn(engine_t *engine, const char *tex, sfVector2f *pos)
{
    sfVector2f size = {220.0F, 60.0F};
    sfVector2u text_size;

    if (tex) {
        text_size = sfTexture_getSize(resources_load_texture(engine->resources, tex));
        size.y = size.x * (float)text_size.y / (float)text_size.x;
    }
    return ui_button_create(engine, tex, pos, &size);
}

static void init_pause_bg(engine_t *engine, pause_menu_t *pause)
{
    sfTexture *texture = resources_load_texture(engine->resources,
        "assets/sprites/main_menu/bg_menu_pause.png");
    sfVector2u text_size = sfTexture_getSize(texture);
    sfColor line_c = {0, 0, 0, 100};

    pause->bg = sfSprite_create();
    sfSprite_setTexture(pause->bg, texture, sfTrue);
    sfSprite_setScale(pause->bg, (sfVector2f){(float)WIN_WIDTH / (float)text_size.x,
        (float)WIN_HEIGHT / (float)text_size.y});
    pause->separator = sfRectangleShape_create();
    sfRectangleShape_setSize(pause->separator, (sfVector2f){4.0F, 500.0F});
    sfRectangleShape_setFillColor(pause->separator, line_c);
    sfRectangleShape_setOrigin(pause->separator, (sfVector2f){2.0F, 250.0F});
    sfRectangleShape_setPosition(pause->separator,
        (sfVector2f){WIN_WIDTH / 2.0F, WIN_HEIGHT / 2.0F});
}

static void init_left(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f p1 = {WIN_WIDTH / 2.0F - 250.0F, WIN_HEIGHT / 2.0F - 100.0F};
    sfVector2f p2 = {p1.x, p1.y + 100.0F};
    sfVector2f p3 = {p1.x, p2.y + 100.0F};
    sfColor w = {255, 255, 255, 255};

    pause->resume = create_btn(engine,
        "assets/sprites/main_menu/button_resume.png", &p1);
    pause->resume->on_click = &pause_on_resume;
    pause->resume->data = engine;
    pause->save = create_btn(engine, NULL, &p2);
    ui_button_set_text(pause->save, "SAVE", 40, &w);
    pause->save->on_click = &pause_on_save;
    pause->save->data = engine;
    pause->exit = create_btn(engine,
        "assets/sprites/main_menu/button_exit.png", &p3);
    pause->exit->on_click = &pause_on_exit;
    pause->exit->data = engine;
}

static void init_right(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f p1 = {WIN_WIDTH / 2.0F + 250.0F, WIN_HEIGHT / 2.0F - 100.0F};
    sfVector2f p2 = {p1.x, p1.y + 100.0F};
    sfVector2f p3 = {p1.x, p2.y + 100.0F};
    sfColor right_way = {255, 255, 255, 255};

    pause->controls = create_btn(engine,
        "assets/sprites/main_menu/button_params.png", &p1);
    pause->controls->on_click = &pause_on_controls;
    pause->controls->data = engine;
    pause->sounds = create_btn(engine, NULL, &p2);
    ui_button_set_text(pause->sounds, "SOUNDS", 40, &right_way);
    pause->sounds->on_click = &pause_on_sounds;
    pause->sounds->data = engine;
    pause->hud = create_btn(engine, NULL, &p3);
    ui_button_set_text(pause->hud, "HUD", 40, &right_way);
    pause->hud->on_click = &pause_on_hud;
    pause->hud->data = engine;
}

void pause_init(engine_t *engine, game_data_t *data)
{
    init_pause_bg(engine, &data->pause);
    init_left(engine, &data->pause);
    init_right(engine, &data->pause);
}
