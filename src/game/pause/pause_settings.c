/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_settings
*/

#include <stdio.h>
#include "graphics/engine.h"
#include "game.h"

void pause_on_controls(void *data)
{
    (void)data;
    puts("Controls licked");
}

void pause_on_sounds(void *data)
{
    (void)data;
    puts("Sounds clicked");
}

void pause_on_hud(void *data)
{
    (void)data;
    puts("HUD clicked");
}
