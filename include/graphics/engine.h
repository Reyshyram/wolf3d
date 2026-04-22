/*
** EPITECH PROJECT, 2025
** engine.h
** File description:
** Header file for the game engine
*/

#ifndef ENGINE_H
// clang-format off
    #define ENGINE_H

    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System.h>
    #include <SFML/System/Types.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/Window/Event.h>
    #include <SFML/Window/Types.h>
    #include <SFML/Window/VideoMode.h>

    #include "graphics/resources.h"

    #define DT_SPEED_MULTIPLIER 1

    #define ASSETS_PATH "assets/"
    #define FONTS_PATH ASSETS_PATH "fonts/"
    #define SPRITES_PATH ASSETS_PATH "sprites/"
    #define MUSICS_PATHS ASSETS_PATH "musics/"
    #define SHADERS_PATH ASSETS_PATH "shaders/"
    #define SFXS_PATHS ASSETS_PATH "sfxs/"

    #define DEFAULT_FONT FONTS_PATH "renogare_regular.otf"
    #define TRANSITION_SPEED 0.2F

    #define TOV2F(v) (sfVector2f) {(float) (v).x, (float) (v).y}
    #define TOV2I(v) (sfVector2i) {(int) (v).x, (int) (v).y}

    #define SUCCESS 0
    #define ERROR 84
// clang-format on

typedef struct engine engine_t;
typedef struct scene scene_t;

enum transition_state {
    TRANSITION_NONE,
    TRANSITION_OUT,
    TRANSITION_IN,
};

struct engine {
    sfRenderWindow *window;
    sfCursor *cursor;
    sfVector2u window_size;
    sfClock *clock;
    float dt;
    sfFont *default_font;
    scene_t *scene;
    scene_t *next_scene;
    resources_t *resources;
    sfRectangleShape *transition_rect;
    float transition_alpha;
    enum transition_state transition_state;
};

struct scene {
    void (*on_enter)(engine_t *engine);
    void (*on_exit)(engine_t *engine);
    void (*update)(engine_t *engine);
    void (*draw)(engine_t *engine);
    void (*handle_events)(engine_t *engine, sfEvent *event);
    void *data;
};

bool is_graphical(char **env);
bool engine_init(engine_t *engine, const char *title, sfVideoMode *video_mode,
    bool is_fullscreen);
void engine_main_loop(engine_t *engine);
void engine_set_scene(engine_t *engine, scene_t *scene, bool transition);
void engine_destroy(engine_t *engine);
void engine_set_cursor(engine_t *engine, const char *path,
    bool set_origin_to_middle);

#endif /* !ENGINE_H */
