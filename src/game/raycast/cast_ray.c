/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** cast_ray
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Vertex.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stddef.h>

#include "game.h"
#include "wolf3d.h"

// clang-format off
static void init_raycast_struct(game_data_t *d, size_t x, ray_t *ray)
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

    ray->camera_plane_x = camera_plane_x;
    ray->ray_dir = ray_dir;
    ray->map_tile = map_tile;
    ray->side_distance = side_distance;
    ray->delta_distance = delta_distance;
    ray->step_dir = step_dir;
}
// clang-format on

static void get_ray_step_dir(ray_t *ray, game_data_t *d)
{
    if (ray->ray_dir.x < 0) {
        ray->step_dir.x = -1;
        ray->side_distance.x = (d->player.pos.x - (float) ray->map_tile.x)
            * ray->delta_distance.x;
    } else {
        ray->step_dir.x = 1;
        ray->side_distance.x = ((float) ray->map_tile.x + 1 - d->player.pos.x)
            * ray->delta_distance.x;
    }
    if (ray->ray_dir.y < 0) {
        ray->step_dir.y = -1;
        ray->side_distance.y = (d->player.pos.y - (float) ray->map_tile.y)
            * ray->delta_distance.y;
    } else {
        ray->step_dir.y = 1;
        ray->side_distance.y = ((float) ray->map_tile.y + 1 - d->player.pos.y)
            * ray->delta_distance.y;
    }
}

static void get_ray_perpendicular_dist(ray_t *ray, game_data_t *d)
{
    while (!ray->was_wall_hit) {
        if (ray->side_distance.x < ray->side_distance.y) {
            ray->side_distance.x += ray->delta_distance.x;
            ray->map_tile.x += ray->step_dir.x;
            ray->was_x_side_hit = true;
        } else {
            ray->side_distance.y += ray->delta_distance.y;
            ray->map_tile.y += ray->step_dir.y;
            ray->was_x_side_hit = false;
        }
        if (d->map[ray->map_tile.x][ray->map_tile.y] > 0)
            ray->was_wall_hit = true;
    }
    if (ray->was_x_side_hit)
        ray->perpendicular_dist = ray->side_distance.x - ray->delta_distance.x;
    else
        ray->perpendicular_dist = ray->side_distance.y - ray->delta_distance.y;
}

// clang-format off
static void get_wall_info(ray_t *ray, game_data_t *d)
{
    ray->camera_plane_length = hypotf(d->camera_plane.x, d->camera_plane.y);
    ray->line_height = (int) ((WALL_HEIGHT_MULT * WIN_WIDTH)
        / (2 * ray->camera_plane_length * ray->perpendicular_dist));
    ray->horizon_y = WIN_HEIGHT / 2 + (int) d->camera_height;
    ray->draw_start_y = -ray->line_height / 2 + ray->horizon_y;
    ray->line_start = ray->draw_start_y;
    if (ray->line_start < 0)
        ray->line_start = 0;
    ray->line_end = ray->line_height / 2 + ray->horizon_y;
    if (ray->line_end >= WIN_HEIGHT)
        ray->line_end = WIN_HEIGHT - 1;
    ray->wall_hit_coord =
        (ray->was_x_side_hit ? d->player.pos.y : d->player.pos.x)
        + ray->perpendicular_dist
        * (ray->was_x_side_hit ? ray->ray_dir.y : ray->ray_dir.x);
    ray->wall_hit_coord = modff(ray->wall_hit_coord, &ray->wall_hit_coord);
}

static void get_ray_texture(ray_t *ray, game_data_t *d)
{
    ray->wall_texture_ind = d->map[ray->map_tile.x][ray->map_tile.y] - 1;
    ray->texture_x = (float) ray->wall_texture_ind * (float) WALL_TEXTURE_WIDTH
        + ray->wall_hit_coord * (float) WALL_TEXTURE_WIDTH;
    ray->texture_y_top = ((float) (ray->line_start - ray->draw_start_y)
        / (float) ray->line_height) * (float) WALL_TEXTURE_HEIGHT;
    ray->texture_y_bottom = ((float) (ray->line_end - ray->draw_start_y)
        / (float) ray->line_height) * (float) WALL_TEXTURE_HEIGHT;
    ray->tint = sfWhite;
    if (!ray->was_x_side_hit) {
        ray->tint.r /= 2;
        ray->tint.g /= 2;
        ray->tint.b /= 2;
    }
}
// clang-format on

static void append_to_vertices(ray_t *ray, game_data_t *d, size_t x)
{
    sfVertexArray_append(d->rays,
        (sfVertex) {{(float) x, (float) ray->line_start}, ray->tint,
            {ray->texture_x, ray->texture_y_top}});
    sfVertexArray_append(d->rays,
        (sfVertex) {{(float) x, (float) ray->line_end}, ray->tint,
            {ray->texture_x, ray->texture_y_bottom}});
}

void cast_ray(game_data_t *d, size_t x)
{
    ray_t ray = {0};

    init_raycast_struct(d, x, &ray);
    get_ray_step_dir(&ray, d);
    get_ray_perpendicular_dist(&ray, d);
    get_wall_info(&ray, d);
    get_ray_texture(&ray, d);
    append_to_vertices(&ray, d, x);
}
