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
    sfView_destroy(hud->mini_map);
    free(hud);
}
