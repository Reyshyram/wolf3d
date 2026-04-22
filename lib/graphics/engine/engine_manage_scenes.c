/*
** EPITECH PROJECT, 2025
** engine_manage_scenes.c
** File description:
** Handle scenes changes
*/

#include <stdlib.h>

#include "graphics/engine.h"

void engine_set_scene(engine_t *engine, scene_t *scene, bool transition)
{
    if (!engine || !scene)
        return;
    if (transition) {
        if (engine->transition_state != TRANSITION_NONE) {
            engine->next_scene = scene;
            return;
        }
        engine->transition_state = TRANSITION_OUT;
        engine->transition_alpha = 0;
        engine->next_scene = scene;
        return;
    }
    if (engine->scene && engine->scene->on_exit) {
        engine->scene->on_exit(engine);
        free(engine->scene);
    }
    engine->scene = scene;
    if (engine->scene->on_enter)
        engine->scene->on_enter(engine);
}
