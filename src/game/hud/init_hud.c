/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** init_hud
*/

#include "game.h"

int init_hud(game_data_t *data)
{
    data->hud = malloc(sizeof(hud_t));
    if (!data->hud)
        return ERROR;
    data->hud->mini_map = sfView_create();
    return SUCCESS;
}
