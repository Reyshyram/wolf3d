/*
** EPITECH PROJECT, 2026
** game.h
** File description:
** game scene
*/

#ifndef GAME_H
// clang-format off
    #define GAME_H

    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>
    #include <stdlib.h>

    #include "graphics/engine.h"
    #include "menu.h"

    #define MAP_HEIGHT 24
    #define MAP_WIDTH 24
    #define WALL_TEXTURE_WIDTH 64
    #define WALL_TEXTURE_HEIGHT 64
    #define WALL_TEXTURES_PATH SPRITES_PATH "wall_textures.png"
    #define NB_WALL_TEXTURES 8

    #define VIGNETTE_SHADER_PATH SHADERS_PATH "vignette.frag"
    #define VIGNETTE_INNER_RADIUS 0.85F
    #define VIGNETTE_OUTER_RADIUS 1.3F
    #define VIGNETTE_ALPHA 0.5F

    #define FLOOR_CEIL_SHADER_PATH SHADERS_PATH "floor_ceil.frag"
    #define FLOOR_TILE_INDEX 3
    #define CEIL_TILE_INDEX 6

    #define ENABLE_FLASHLIGHT true
    #define FLASHLIGHT_RANGE 2
    #define FLASHLIGHT_MIN_LIGHT 0

    #define WALL_HEIGHT_MULT 1

    #define MOVE_SPEED 5
    #define SPRINT_MULT 1.5F
    #define CROUCH_MULT 0.5F
    #define COLLISION_MARGIN 0.1F

    #define CAMERA_ROT_SPEED 1
    #define CAMERA_HEIGHT_SPEED 1000
    #define ZOOM_FACTOR 1.5F

    #define MOUSE_X_SENSITIVITY 0.002F
    #define MOUSE_Y_SENSITIVITY 2.0F

    #define DEFAULT_FOV 0.66F
    #define SPRINT_FOV 0.8F
    #define CROUCH_FOV 0.5F

    #define MINIMAP_TILE_SIZE 2
    #define MINIMAP_RATIO 3
    #define MINIMAP_VIEWPORT (sfFloatRect) {0.75F, 0.05F, 0.25F, 0.25F}
    #define MINIMAP_OPACITY 160

    #define TIMER_POS (sfVector2f) {50, 50}
// clang-format on

typedef struct {
    sfVector2f pos;
    sfVector2f view_dir;
    bool has_moved;
    bool is_sprinting;
    bool is_crouching;
    bool is_zooming;
} player_t;

typedef struct hud_s {
    sfView *mini_map;
    sfRenderTexture *mini_map_render;
    sfCircleShape *mini_map_shape;
    sfVector2u mini_map_size;
    sfText *timer;
    float timer_time;
} hud_t;

typedef struct game_s {
    int map[MAP_WIDTH][MAP_HEIGHT];
    sfRenderTexture *render_texture;
    sfVertexArray *rays;
    sfRectangleShape *floor_ceil;
    sfShader *floor_ceil_shader;
    sfShader *vignette_shader;
    sfTexture *wall_textures;
    player_t player;
    sfVector2f camera_plane;
    sfVector2f camera_plane_base;
    float camera_height;
    float fov;
    float target_fov;
    float bobbing_clock;
    hud_t *hud;
    bool is_paused;
    pause_menu_t pause;
} game_data_t;

typedef struct ray_s {
    float camera_plane_x;
    sfVector2f ray_dir;
    sfVector2i map_tile;
    sfVector2f side_distance;
    sfVector2f delta_distance;
    sfVector2i step_dir;
    float perpendicular_dist;
    bool was_wall_hit;
    bool was_x_side_hit;
    float camera_plane_length;
    int line_height;
    int horizon_y;
    int draw_start_y;
    int line_start;
    int line_end;
    float wall_hit_coord;
    int wall_texture_ind;
    float texture_x;
    float texture_y_top;
    float texture_y_bottom;
    sfColor tint;
} ray_t;

scene_t *game_create(void);
void game_enter(engine_t *engine);
void game_exit(engine_t *engine);
void game_draw(engine_t *engine);
void game_update(engine_t *engine);
void game_event(engine_t *engine, sfEvent *event);

void cast_wall_ray(game_data_t *d, size_t x);
void draw_floor_and_ceil(game_data_t *d);

int init_hud(engine_t *engine, game_data_t *data);
void free_hud(hud_t *hud);
void view_mini_map(engine_t *engine, game_data_t *d, hud_t *hud);
void draw_timer(engine_t *engine, hud_t *hud);

#endif /* !GAME_H */
