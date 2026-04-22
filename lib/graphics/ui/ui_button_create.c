/*
** EPITECH PROJECT, 2025
** ui_button_create.c
** File description:
** Create an ui button
*/

#include <SFML/Config.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/ui.h"

ui_button_t *ui_button_create(engine_t *engine, const char *texture_path,
    sfVector2f *pos, sfVector2f *size)
{
    ui_button_t *button = malloc(sizeof(*button));
    sfFloatRect bounds;

    if (!button)
        return nullptr;
    memset(button, 0, sizeof(*button));
    button->background = sfRectangleShape_create();
    sfRectangleShape_setPosition(button->background, *pos);
    sfRectangleShape_setSize(button->background, *size);
    sfRectangleShape_setTexture(button->background,
        resources_load_texture(engine->resources, texture_path), sfTrue);
    bounds = sfRectangleShape_getLocalBounds(button->background);
    sfRectangleShape_setOrigin(button->background,
        (sfVector2f) {bounds.width / 2, bounds.height / 2});
    button->text = sfText_create();
    sfText_setFont(button->text, engine->default_font);
    button->scale = (sfVector2f) {1, 1};
    button->char_size = 16;
    return button;
}
