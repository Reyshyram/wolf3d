/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** menu
*/

#ifndef MENU_H_
    #define MENU_H_

    #include "graphics/engine.h"
    #include "graphics/ui.h"

typedef struct menu_data {
    sfSprite *bg;
    sfSprite *logo;
    ui_button_t *play_btn;
    ui_button_t *exit_btn;
} menu_data_t;

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

#endif /* !MENU_H_ */
