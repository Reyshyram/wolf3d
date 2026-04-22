/*
** EPITECH PROJECT, 2025
** is_graphical.c
** File description:
** Check if the environment has graphical support
*/

#include <string.h>

bool is_graphical(char **env)
{
    for (int i = 0; env[i]; i++)
        if (strncmp(env[i], "DISPLAY=", 8) == 0
            || strncmp(env[i], "WAYLAND_DISPLAY=", 16) == 0)
            return true;
    return false;
}
