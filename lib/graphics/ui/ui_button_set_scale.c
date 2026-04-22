/*
** EPITECH PROJECT, 2025
** ui_button_set_scale.c
** File description:
** Set the text of an UI button
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/System/Vector2.h>

#include "graphics/ui.h"

ui_button_t *ui_button_set_scale(ui_button_t *button, const sfVector2f *scale)
{
    if (!button || !scale)
        return nullptr;
    button->scale = *scale;
    sfRectangleShape_setScale(button->background, button->scale);
    sfText_setCharacterSize(button->text,
        (unsigned int) button->scale.x * button->char_size);
    return button;
}
