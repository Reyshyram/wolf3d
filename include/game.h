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

    #include "graphics/engine.h"

    #define MAP_HEIGHT 24
    #define MAP_WIDTH 24
    #define WALL_TEXTURE_WIDTH 64
    #define WALL_TEXTURE_HEIGHT 64
    #define WALL_TEXTURES_PATH SPRITES_PATH "wall_textures.png"

    #define WALL_HEIGHT_MULT 1

    #define MOVE_SPEED 5
    #define COLLISION_MARGIN 0.1F

    #define CAMERA_ROT_SPEED 1
    #define CAMERA_HEIGHT_SPEED 1000

    #define MOUSE_X_SENSITIVITY 0.002F
    #define MOUSE_Y_SENSITIVITY 2.0F
// clang-format on

typedef struct {
    sfVector2f pos;
    sfVector2f view_dir;
} player_t;

typedef struct game_s {
    int map[MAP_WIDTH][MAP_HEIGHT];
    sfVertexArray *rays;
    sfTexture *wall_textures;
    player_t player;
    sfVector2f camera_plane;
    float camera_height;
} game_data_t;

scene_t *game_create(void);
void game_enter(engine_t *engine);
void game_exit(engine_t *engine);
void game_draw(engine_t *engine);
void game_update(engine_t *engine);
void game_event(engine_t *engine, sfEvent *event);

#endif /* !GAME_H */
