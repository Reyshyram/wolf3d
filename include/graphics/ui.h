/*
** EPITECH PROJECT, 2025
** graphiccs/ui.h
** File description:
** Header file for the engine ui system
*/

#ifndef ENGINE_UI_H
// clang-format off
    #define ENGINE_UI_H

    #include "graphics/engine.h"

    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>
    #include <stdbool.h>
// clang-format on

typedef struct ui_button ui_button_t;

struct ui_button {
    sfRectangleShape *background;
    sfText *text;
    sfVector2f scale;
    unsigned int char_size;
    bool hovered;
    void (*on_click)(void *);
    void *data;
};

ui_button_t *ui_button_create(engine_t *engine, const char *texture_path,
    sfVector2f *pos, sfVector2f *size);
void ui_button_destroy(ui_button_t *button);
void ui_button_update(engine_t *engine, ui_button_t *button);
void ui_button_events(ui_button_t *button, const sfEvent *event,
    const engine_t *engine);
ui_button_t *ui_button_set_text(ui_button_t *button, const char *text,
    int char_size, sfColor *color);
ui_button_t *ui_button_set_scale(ui_button_t *button, const sfVector2f *scale);

#endif /* !ENGINE_UI_H */
