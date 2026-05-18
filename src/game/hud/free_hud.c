/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** free_hud
*/

#include "game.h"

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
    free(hud);
}
