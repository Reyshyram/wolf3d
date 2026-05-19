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
    ui_button_t *play_btn;
    ui_button_t *exit_btn;
} menu_data_t;



#endif /* !MENU_H_ */
