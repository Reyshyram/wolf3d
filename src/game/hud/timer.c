/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** timer
*/

#include <stdio.h>

#include "graphics/engine.h"

#include "game.h"

void draw_timer(engine_t *engine, hud_t *hud)
{
    char buf[16];
    float time = hud->timer_time * 1000;
    int cs = ((int) time % 1000) / 10;
    int sec = ((int) time / 1000) % 60;
    int min = (int) time / 60000;

    snprintf(buf, sizeof(buf), "%02d:%02d.%02d", min, sec, cs);
    sfText_setString(hud->timer, buf);
    sfRenderWindow_drawText(engine->window, hud->timer, NULL);
}
