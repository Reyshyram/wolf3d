/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** menu
*/

// clang-format off
#ifndef MENU_H_
    #define MENU_H_

    #include "graphics/engine.h"
    #include "graphics/sprite_anim.h"
    #include "graphics/ui.h"

    #define LOGO_FRAMES 5
    #define LOGO_FPS 12.0F
    #define LOGO_WIDTH 381
    #define LOGO_HEIGHT 112
// clang-format on

typedef struct menu_data {
    sfSprite *bg;
    sprite_anim_t *logo;
    ui_button_t *play_btn;
    ui_button_t *exit_btn;
} menu_data_t;

typedef enum pause_page {
    PAUSE_PAGE_MAIN,
    PAUSE_PAGE_CONTROLS,
    PAUSE_PAGE_SOUNDS,
    PAUSE_PAGE_HUD,
} pause_page_t;

typedef struct pause_menu {
    sfSprite *bg;
    sfRectangleShape *separator;
    pause_page_t page;
    ui_button_t *resume;
    ui_button_t *save;
    ui_button_t *exit;
    ui_button_t *controls;
    ui_button_t *sounds;
    ui_button_t *hud;
    ui_button_t *back;
    ui_button_t *controls_move;
    ui_button_t *controls_camera;
    ui_button_t *controls_pause;
    ui_button_t *sound_master;
    ui_button_t *sound_steps;
    ui_button_t *hud_minimap;
    ui_button_t *hud_timer;
} pause_menu_t;

// Main_menu

typedef struct game_s game_data_t;

scene_t *menu_create(void);
void menu_on_enter(engine_t *engine);
void menu_update(engine_t *engine);
void menu_draw(engine_t *engine);
void handle_menu_events(engine_t *engine, sfEvent *event);
void menu_on_exit(engine_t *engine);
void init_sprites(engine_t *engine, menu_data_t *data);
void init_buttons(engine_t *engine, menu_data_t *data);
void on_play_click(void *data);
void on_exit_click(void *data);
// Pause_menu
void pause_on_resume(void *data);
void pause_on_save(void *data);
void pause_on_exit(void *data);
void pause_on_back(void *data);
void pause_init(engine_t *engine, game_data_t *data);
void pause_destroy(game_data_t *data);
void draw_btn(engine_t *engine, ui_button_t *button);
void pause_draw(engine_t *engine, game_data_t *data);
void pause_events(engine_t *engine, game_data_t *data, sfEvent *event);
void pause_on_hud(void *data);
void pause_on_sounds(void *data);
void pause_on_controls(void *data);
void pause_on_sound_master(void *data);
void pause_on_sound_steps(void *data);
void pause_on_hud_minimap(void *data);
void pause_on_hud_timer(void *data);
void pause_update(engine_t *engine, game_data_t *data);
// Utils
ui_button_t *create_btn(engine_t *engine, const char *tex,
    sfVector2f *pos);
void init_setting_btn(ui_button_t *button, engine_t *engine,
    void (*on_click)(void *), const char *label);
ui_button_t *create_text_btn(engine_t *engine, sfVector2f *pos,
    sfVector2f *size, const char *label);
ui_button_t *destroy_text_btn(ui_button_t *button);
void set_pause_page(engine_t *engine, pause_page_t page);
void set_button_state(ui_button_t *button, const char *label,
    bool enabled);

#endif /* !MENU_H_ */
