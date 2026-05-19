/*
** EPITECH PROJECT, 2026
** wolf3d [WSL: Ubuntu]
** File description:
** menu_create
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "menu.h"
#include "wolf3d.h"

void init_sprites(engine_t *engine, menu_data_t *data)
{
    sfTexture *texture_bg = resources_load_texture(engine->resources,
        "assets/sprites/main_menu/background.png");
    sfTexture *texture_logo = resources_load_texture(engine->resources,
        "assets/sprites/main_menu/logo.png");
    sfFloatRect bounds;

    data->bg = sfSprite_create();
    sfSprite_setTexture(data->bg, texture_bg, sfTrue);
    data->logo = sfSprite_create();
    sfSprite_setTexture(data->logo, texture_logo, sfTrue);
    bounds = sfSprite_getLocalBounds(data->logo);
    sfSprite_setOrigin(data->logo, (sfVector2f){bounds.width / 2.0F,
            bounds.height / 2.0F});
    sfSprite_setPosition(data->logo, (sfVector2f){WIN_WIDTH / 2.0F, 150.0F});
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
