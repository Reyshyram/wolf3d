/*
** EPITECH PROJECT, 2025
** ui_button_update.c
** File description:
** Update an UI button
*/

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/System/Vector2.h>

#include "graphics/engine.h"
#include "graphics/maths.h"
#include "graphics/ui.h"

static void update_bg_scale(const engine_t *engine, ui_button_t *button)
{
    sfVector2f target_scale = button->scale;
    sfVector2f original_scale = sfRectangleShape_getScale(button->background);
    sfVector2f new_scale;

    if (button->hovered) {
        target_scale.x *= 1.1F;
        target_scale.y *= 1.1F;
    }
    new_scale = (sfVector2f) {
        interpolatef(original_scale.x, target_scale.x, engine->dt * 8),
        interpolatef(original_scale.y, target_scale.y, engine->dt * 8)};
    sfRectangleShape_setScale(button->background, new_scale);
}

static void update_text_scale(const engine_t *engine, ui_button_t *button)
{
    float text_target_scale = 1;
    sfVector2f original_text_scale = sfText_getScale(button->text);
    sfVector2f new_text_scale;

    if (button->hovered)
        text_target_scale = 1.1F;
    new_text_scale = (sfVector2f) {
        interpolatef(original_text_scale.x, text_target_scale, engine->dt * 8),
        interpolatef(original_text_scale.y, text_target_scale,
            engine->dt * 8)};
    sfText_setScale(button->text, new_text_scale);
}

void ui_button_update(engine_t *engine, ui_button_t *button)
{
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(engine->window,
        sfMouse_getPositionRenderWindow(engine->window), nullptr);
    sfFloatRect button_bounds =
        sfRectangleShape_getGlobalBounds(button->background);

    button->hovered =
        sfFloatRect_contains(&button_bounds, mouse_pos.x, mouse_pos.y);
    update_bg_scale(engine, button);
    update_text_scale(engine, button);
}
