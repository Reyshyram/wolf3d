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
