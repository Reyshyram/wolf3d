/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** timer
*/

#include "graphics/engine.h"

#include "game.h"
#include "wolf3d.h"

#include <stdio.h>

void draw_timer(engine_t *engine, hud_t *hud)
{
    char *buf = malloc(sizeof(char) * 7);
    float time = sfTime_asMilliseconds(sfClock_getElapsedTime(hud->clock));
    int ms = ((int)time % 1000) / 100;
    int sec = ((int)time / 1000) % 60;
    int min = time / 60000;

    sprintf(buf, "%02d:%02d:%d", min, sec, ms);
    sfText_setString(hud->timer, buf);
    sfRenderWindow_drawText(engine->window, hud->timer, NULL);
    free(buf);
}
