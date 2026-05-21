/*
** EPITECH PROJECT, 2026
** game_exit.c
** File description:
** Exit the game scene
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Shader.h>
#include <SFML/Graphics/VertexArray.h>
#include <stdlib.h>

#include "graphics/engine.h"

#include "game.h"
#include "menu.h"
#include "weapons.h"

void game_exit(engine_t *engine)
{
    game_data_t *data = (game_data_t *) engine->scene->data;

    if (!data)
        return;
    if (data->floor_ceil_shader)
        sfShader_destroy(data->floor_ceil_shader);
    if (data->vignette_shader)
        sfShader_destroy(data->vignette_shader);
    if (data->rays)
        sfVertexArray_destroy(data->rays);
    if (data->floor_ceil)
        sfRectangleShape_destroy(data->floor_ceil);
    sfRenderTexture_destroy(data->render_texture);
    free_hud(data->hud);
    free_weapons(data);
    pause_destroy(data);
    free(data);
    sfRenderWindow_setMouseCursorVisible(engine->window, true);
}
