/*
** EPITECH PROJECT, 2026
** game_create.c
** File description:
** Create game scene
*/

#include <stdlib.h>
#include <string.h>

#include "graphics/engine.h"

#include "game.h"

scene_t *game_create(void)
{
    scene_t *scene = malloc(sizeof(*scene));

    if (!scene)
        return nullptr;
    scene->on_enter = game_enter;
    scene->on_exit = game_exit;
    scene->draw = game_draw;
    scene->update = game_update;
    scene->handle_events = game_event;
    scene->data = malloc(sizeof(game_data_t));
    if (!scene->data) {
        free(scene);
        return nullptr;
    }
    memset(scene->data, 0, sizeof(game_data_t));
    return scene;
}
