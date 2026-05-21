/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_buttons_utils
*/

#include "game.h"
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/ui.h"
#include "menu.h"
#include "wolf3d.h"

ui_button_t *create_btn(engine_t *engine, const char *tex,
    sfVector2f *pos)
{
    sfVector2f size = {220.0F, 60.0F};
    sfVector2u text_size;

    if (tex) {
        text_size =
            sfTexture_getSize(resources_load_texture(engine->resources, tex));
        size.y = size.x * (float) text_size.y / (float) text_size.x;
    }
    return ui_button_create(engine, tex, pos, &size);
}

void init_setting_btn(ui_button_t *button, engine_t *engine,
    void (*on_click)(void *), const char *label)
{
    sfColor color = sfWhite;

    if (!button)
        return;
    ui_button_set_text(button, label, 14, &color);
    button->on_click = on_click;
    button->data = engine;
}

ui_button_t *create_text_btn(engine_t *engine, sfVector2f *pos,
    sfVector2f *size, const char *label)
{
    ui_button_t *button = calloc(1, sizeof(*button));
    sfColor color = sfWhite;

    if (!button)
        return nullptr;
    button->background = sfRectangleShape_create();
    button->text = sfText_create();
    if (!button->background || !button->text) {
        destroy_text_btn(button);
        return nullptr;
    }
    sfRectangleShape_setPosition(button->background, *pos);
    sfRectangleShape_setSize(button->background, *size);
    sfRectangleShape_setFillColor(button->background,
        sfColor_fromRGBA(0, 0, 0, 40));
    sfRectangleShape_setTexture(button->background, nullptr, sfTrue);
    sfText_setFont(button->text, engine->default_font);
    button->scale = (sfVector2f) {1, 1};
    button->char_size = 14;
    ui_button_set_text(button, label, 14, &color);
    return button;
}

void destroy_text_btn(ui_button_t *button)
{
    if (button->background)
        sfRectangleShape_destroy(button->background);
    if (button->text)
        sfText_destroy(button->text);
    free(button);
}
