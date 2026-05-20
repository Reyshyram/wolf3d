/*
** EPITECH PROJECT, 2026
** wolf3d [WSL: Ubuntu]
** File description:
** menu_create
*/

#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/sprite_anim.h"
#include "menu.h"
#include "wolf3d.h"
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>

void init_buttons(engine_t *engine, menu_data_t *data)
{
    sfVector2u text_size = sfTexture_getSize(resources_load_texture(
            engine->resources, "assets/sprites/main_menu/button_play.png"));
    sfVector2f size = {350.0F,
        350.0F * (float) text_size.y / (float) text_size.x};
    sfVector2f pos_p = {WIN_WIDTH / 2.0F, WIN_HEIGHT / 2.0F - 20.0F};
    sfVector2f pos_e = {WIN_WIDTH / 2.0F, pos_p.y + size.y + 40.0F};

    data->play_btn = ui_button_create(engine,
        "assets/sprites/main_menu/button_play.png", &pos_p, &size);
    data->play_btn->on_click = &on_play_click;
    data->play_btn->data = engine;
    data->exit_btn = ui_button_create(engine,
        "assets/sprites/main_menu/button_exit.png", &pos_e, &size);
    data->exit_btn->on_click = &on_exit_click;
    data->exit_btn->data = engine;
}

void init_sprites(engine_t *engine, menu_data_t *data)
{
    sfTexture *texture_bg = resources_load_texture(engine->resources,
        "assets/sprites/main_menu/background.jpg");
    sfVector2u bg_size = sfTexture_getSize(texture_bg);
    const sprite_frame_info_t info = {{0, 0, LOGO_WIDTH, LOGO_HEIGHT},
        LOGO_FRAMES, LOGO_FPS};

    data->bg = sfSprite_create();
    sfSprite_setTexture(data->bg, texture_bg, sfTrue);
    sfSprite_setScale(data->bg,
        (sfVector2f) {(float) WIN_WIDTH / (float) bg_size.x,
            (float) WIN_HEIGHT / (float) bg_size.y});
    data->logo =
        sprite_anim_create("assets/sprites/main_menu/logo.png", &info, engine);
    sfSprite_setOrigin(data->logo->sprite,
        (sfVector2f) {LOGO_WIDTH / 2.0F, LOGO_HEIGHT / 2.0F});
    sfSprite_setScale(data->logo->sprite,
        (sfVector2f) {(float) WIN_WIDTH / LOGO_WIDTH * 0.65F,
            (float) WIN_WIDTH / LOGO_WIDTH * 0.65F});
    sfSprite_setPosition(data->logo->sprite,
        (sfVector2f) {WIN_WIDTH / 2.0F, 150.0F});
}

scene_t *menu_create(void)
{
    scene_t *scene = malloc(sizeof(scene_t));
    menu_data_t *data = calloc(1, sizeof(menu_data_t));

    if (!scene || !data)
        return NULL;
    scene->data = data;
    scene->on_enter = &menu_on_enter;
    scene->update = &menu_update;
    scene->draw = &menu_draw;
    scene->handle_events = &handle_menu_events;
    scene->on_exit = &menu_on_exit;
    return scene;
}
