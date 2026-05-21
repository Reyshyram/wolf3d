/*
** EPITECH PROJECT, 2026
** game_draw.c
** File description:
** Draw the game scene
*/

#include <SFML/Graphics/RenderStates.h>
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <math.h>
#include <stddef.h>

#include "graphics/engine.h"

#include "game.h"
#include "menu.h"
#include "weapons.h"
#include "wolf3d.h"

static void apply_bobbing(float dt, game_data_t *d, engine_t *engine)
{
    float mult = 1;

    if (d->player.has_moved) {
        d->bobbing_clock += dt * 10;
        if (d->player.is_sprinting)
            mult = SPRINT_MULT;
        if (d->player.is_crouching)
            mult = CROUCH_MULT;
        if (d->player.is_zooming)
            mult /= 2;
        d->camera_height += sinf(d->bobbing_clock)
            / (NORMAL_BOBBING / (float) engine->window_size.y) * mult;
    } else
        d->bobbing_clock = 0;
}

static void draw_environment(engine_t *engine, game_data_t *d)
{
    sfRenderStates states = sfRenderStates_default();
    const sfTexture *render = sfRenderTexture_getTexture(d->render_texture);
    sfSprite *sprite = sfSprite_create();

    if (!sprite)
        return;
    sfVertexArray_clear(d->rays);
    draw_floor_and_ceil(engine, d);
    for (size_t x = 0; x <= engine->window_size.x; x++)
        cast_wall_ray(engine, d, x);
    states.texture = d->wall_textures;
    sfRenderTexture_drawVertexArray(d->render_texture, d->rays, &states);
    sfRenderTexture_display(d->render_texture);
    apply_bobbing(engine->dt, d, engine);
    sfSprite_setTexture(sprite, render, true);
    sfRenderWindow_drawSprite(engine->window, sprite, nullptr);
    sfSprite_destroy(sprite);
}

static void draw_vignette(engine_t *engine, game_data_t *d)
{
    sfRenderStates states = sfRenderStates_default();

    states.shader = d->vignette_shader;
    sfRenderWindow_drawRectangleShape(engine->window, d->floor_ceil, &states);
}

void game_draw(engine_t *engine)
{
    game_data_t *d = (game_data_t *) engine->scene->data;

    if (!d)
        return;
    draw_environment(engine, d);
    draw_vignette(engine, d);
    draw_weapon(engine, d);
    if (d->hud && d->hud->show_minimap)
        view_mini_map(engine, d, d->hud);
    if (d->hud && d->hud->show_timer)
        draw_timer(engine, d->hud);
    draw_weapon_hud(engine, d);
    if (d->is_paused)
        pause_draw(engine, d);
}
