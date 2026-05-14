/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** draw_floor_and_ceil
*/

#include <SFML/Graphics/Glsl.h>
#include <SFML/Graphics/RenderStates.h>
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/Shader.h>
#include <SFML/System/Vector2.h>
#include <math.h>

#include "game.h"
#include "wolf3d.h"

static void set_shader_uniforms(game_data_t *d, sfVector2f *ray_dir_left,
    sfVector2f *ray_dir_right)
{
    sfShader_setVec2Uniform(d->floor_ceil_shader, "u_player_pos",
        (sfGlslVec2) {d->player.pos.x, d->player.pos.y});
    sfShader_setVec2Uniform(d->floor_ceil_shader, "u_ray_dir_left",
        (sfGlslVec2) {ray_dir_left->x, ray_dir_left->y});
    sfShader_setVec2Uniform(d->floor_ceil_shader, "u_ray_dir_right",
        (sfGlslVec2) {ray_dir_right->x, ray_dir_right->y});
}

void draw_floor_and_ceil(game_data_t *d)
{
    sfRenderStates states = sfRenderStates_default();
    sfVector2f ray_dir_left = {d->player.view_dir.x - d->camera_plane.x,
        d->player.view_dir.y - d->camera_plane.y};
    sfVector2f ray_dir_right = {d->player.view_dir.x + d->camera_plane.x,
        d->player.view_dir.y + d->camera_plane.y};
    float horizon_y = (float) WIN_HEIGHT / 2 + d->camera_height;
    float camera_plane_len = hypotf(d->camera_plane.x, d->camera_plane.y);
    float plane_dist = ((float) WIN_WIDTH * (float) WALL_HEIGHT_MULT)
        / (2.0F * camera_plane_len);

    set_shader_uniforms(d, &ray_dir_left, &ray_dir_right);
    sfShader_setFloatUniform(d->floor_ceil_shader, "u_horizon_y",
        WIN_HEIGHT - horizon_y);
    sfShader_setFloatUniform(d->floor_ceil_shader, "u_plane_dist", plane_dist);
    states.shader = d->floor_ceil_shader;
    sfRenderTexture_drawRectangleShape(d->render_texture, d->floor_ceil,
        &states);
}
