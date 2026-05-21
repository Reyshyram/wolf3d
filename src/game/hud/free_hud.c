/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** free_hud
*/

#include "game.h"
#include "graphics/sprite_anim.h"

void free_hud(hud_t *hud)
{
    if (!hud)
        return;
    if (hud->mini_map_shape)
        sfCircleShape_destroy(hud->mini_map_shape);
    if (hud->mini_map_render)
        sfRenderTexture_destroy(hud->mini_map_render);
    if (hud->mini_map)
        sfView_destroy(hud->mini_map);
    if (hud->timer)
        sfText_destroy(hud->timer);
    if (hud->cursor)
        sprite_anim_destroy(hud->cursor);
    if (hud->ammo_sprite)
        sfSprite_destroy(hud->ammo_sprite);
    if (hud->ammo_text)
        sfText_destroy(hud->ammo_text);
    free(hud);
}
