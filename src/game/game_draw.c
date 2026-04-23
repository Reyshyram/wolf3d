/*
** EPITECH PROJECT, 2026
** game_draw.c
** File description:
** Draw the game scene
*/

#include <SFML/Graphics/RenderStates.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/VertexArray.h>
#include <stddef.h>

#include "graphics/engine.h"

#include "game.h"
#include "wolf3d.h"

void game_draw(engine_t *engine)
{
    game_data_t *d = (game_data_t *) engine->scene->data;
    sfRenderStates states = sfRenderStates_default();

    if (!d)
        return;
    sfVertexArray_clear(d->rays);
    for (size_t x = 0; x < WIN_WIDTH; x++)
        cast_ray(d, x);
    states.texture = d->wall_textures;
    sfRenderWindow_drawVertexArray(engine->window, d->rays, &states);
}
