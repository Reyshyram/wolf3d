/*
** EPITECH PROJECT, 2026
** game_resize.c
** File description:
** resize the game
*/

#include <SFML/Graphics/Glsl.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/Graphics/View.h>
#include <SFML/Window/Mouse.h>

#include "graphics/engine.h"

#include "game.h"

static void resize_render(game_data_t *d, unsigned int w, unsigned int h)
{
    sfVertexArray_resize(d->rays, (size_t) w * 2);
    sfRectangleShape_setSize(d->floor_ceil,
        (sfVector2f) {(float) w, (float) h});
    sfShader_setVec2Uniform(d->floor_ceil_shader, "u_resolution",
        (sfGlslVec2) {(float) w, (float) h});
    sfShader_setVec2Uniform(d->vignette_shader, "u_resolution",
        (sfGlslVec2) {(float) w, (float) h});
    sfRenderTexture_destroy(d->render_texture);
    d->render_texture = sfRenderTexture_create(w, h, false);
}

void game_on_resize(engine_t *engine)
{
    game_data_t *d = (game_data_t *) engine->scene->data;
    unsigned int w = engine->window_size.x;
    unsigned int h = engine->window_size.y;
    float timer = 0;

    resize_render(d, w, h);
    timer = d->hud->timer_time;
    free_hud(d->hud);
    init_hud(engine, d);
    d->hud->timer_time = timer;
    sfRenderWindow_setMouseCursorVisible(engine->window, false);
    sfMouse_setPositionRenderWindow((sfVector2i) {(int) w / 2, (int) h / 2},
        engine->window);
}
