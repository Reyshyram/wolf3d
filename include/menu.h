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
} menu_data_t;

scene_t *menu_create(void);
void menu_on_enter(engine_t *engine);
void menu_update(engine_t *engine);
void menu_draw(engine_t *engine);
void handle_menu_events(engine_t *engine, sfEvent *event);
void menu_on_exit(engine_t *engine);
void init_sprites(engine_t *engine, menu_data_t *data);

#endif /* !MENU_H_ */
