/*
** EPITECH PROJECT, 2025
** ui_button_set_text.c
** File description:
** Set the text of an UI button
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/System/Vector2.h>

#include "graphics/ui.h"

ui_button_t *ui_button_set_text(ui_button_t *button, const char *text,
    int char_size, sfColor *color)
{
    sfFloatRect text_bounds;

    if (!button || !text || !color)
        return nullptr;
    sfText_setString(button->text, text);
    if (char_size > 0)
        sfText_setCharacterSize(button->text,
            (unsigned int) (button->scale.x * char_size));
    if (color)
        sfText_setFillColor(button->text, *color);
    text_bounds = sfText_getLocalBounds(button->text);
    sfText_setOrigin(button->text,
        (sfVector2f) {text_bounds.left + text_bounds.width / 2,
            text_bounds.top + text_bounds.height / 2});
    sfText_setPosition(button->text,
        sfRectangleShape_getPosition(button->background));
    return button;
}
