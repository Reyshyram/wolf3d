/*
** EPITECH PROJECT, 2025
** ui_button_destroy
** File description:
** Destroy an UI button
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <stdlib.h>

#include "graphics/ui.h"

void ui_button_destroy(ui_button_t *button)
{
    if (!button)
        return;
    if (button->background)
        sfRectangleShape_destroy(button->background);
    if (button->text)
        sfText_destroy(button->text);
    free(button);
}
