/*
** EPITECH PROJECT, 2026
** game_exit.c
** File description:
** Exit the game scene
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/VertexArray.h>
#include <stdlib.h>

#include "graphics/engine.h"

#include "game.h"

void game_exit(engine_t *engine)
{
    game_data_t *data = (game_data_t *) engine->scene->data;

    if (!data)
        return;
    if (data->rays)
        sfVertexArray_destroy(data->rays);
    free(data);
    sfRenderWindow_setMouseCursorVisible(engine->window, true);
}
