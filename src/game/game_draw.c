/*
** EPITECH PROJECT, 2026
** game_draw.c
** File description:
** Draw the game scene
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderStates.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Vertex.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stddef.h>

#include "graphics/engine.h"

#include "game.h"
#include "wolf3d.h"

static void cast_ray(game_data_t *d, size_t x)
{
    float camera_plane_x = 2.F * (float) x / (float) WIN_WIDTH - 1;
    sfVector2f ray_dir = {d->player.view_dir.x
            + d->camera_plane.x * camera_plane_x,
        d->player.view_dir.y + d->camera_plane.y * camera_plane_x};
    sfVector2i map_tile = {(int) d->player.pos.x, (int) d->player.pos.y};
    sfVector2f side_distance = {0, 0};
    sfVector2f delta_distance = {fabsf(1.F / ray_dir.x),
        fabsf(1.F / ray_dir.y)};
    sfVector2i step_dir = {0, 0};
    float perpendicular_distance = 0;
    bool was_wall_hit = false;
    bool was_x_side_hit = false;

    if (ray_dir.x < 0) {
        step_dir.x = -1;
        side_distance.x =
            (d->player.pos.x - (float) map_tile.x) * delta_distance.x;
    } else {
        step_dir.x = 1;
        side_distance.x =
            ((float) map_tile.x + 1 - d->player.pos.x) * delta_distance.x;
    }
    if (ray_dir.y < 0) {
        step_dir.y = -1;
        side_distance.y =
            (d->player.pos.y - (float) map_tile.y) * delta_distance.y;
    } else {
        step_dir.y = 1;
        side_distance.y =
            ((float) map_tile.y + 1 - d->player.pos.y) * delta_distance.y;
    }
    while (!was_wall_hit) {
        if (side_distance.x < side_distance.y) {
            side_distance.x += delta_distance.x;
            map_tile.x += step_dir.x;
            was_x_side_hit = true;
        } else {
            side_distance.y += delta_distance.y;
            map_tile.y += step_dir.y;
            was_x_side_hit = false;
        }
        if (d->map[map_tile.x][map_tile.y] > 0)
            was_wall_hit = true;
    }
    if (was_x_side_hit)
        perpendicular_distance = side_distance.x - delta_distance.x;
    else
        perpendicular_distance = side_distance.y - delta_distance.y;

    float camera_plane_length = hypotf(d->camera_plane.x, d->camera_plane.y);
    int line_height = (int) ((WALL_HEIGHT_MULT * WIN_WIDTH)
        / (2 * camera_plane_length * perpendicular_distance));
    int horizon_y = WIN_HEIGHT / 2 + (int) d->camera_height;

    int draw_start_y = -line_height / 2 + horizon_y;

    int line_start = draw_start_y;
    if (line_start < 0)
        line_start = 0;
    int line_end = line_height / 2 + horizon_y;
    if (line_end >= WIN_HEIGHT)
        line_end = WIN_HEIGHT - 1;

    float wall_hit_coordinate =
        (was_x_side_hit ? d->player.pos.y : d->player.pos.x)
        + perpendicular_distance * (was_x_side_hit ? ray_dir.y : ray_dir.x);
    wall_hit_coordinate = modff(wall_hit_coordinate, &wall_hit_coordinate);

    int wall_texture_index = d->map[map_tile.x][map_tile.y] - 1;
    float texture_x = (float) wall_texture_index * (float) WALL_TEXTURE_WIDTH
        + wall_hit_coordinate * (float) WALL_TEXTURE_WIDTH;

    float texture_y_top =
        ((float) (line_start - draw_start_y) / (float) line_height)
        * (float) WALL_TEXTURE_HEIGHT;
    float texture_y_bottom =
        ((float) (line_end - draw_start_y) / (float) line_height)
        * (float) WALL_TEXTURE_HEIGHT;

    sfColor tint = sfWhite;
    if (!was_x_side_hit) {
        tint.r /= 2;
        tint.g /= 2;
        tint.b /= 2;
    }
    sfVertexArray_append(d->rays,
        (sfVertex) {{(float) x, (float) line_start}, tint,
            {texture_x, texture_y_top}});
    sfVertexArray_append(d->rays,
        (sfVertex) {{(float) x, (float) line_end}, tint,
            {texture_x, texture_y_bottom}});
}

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
