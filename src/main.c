/*
** EPITECH PROJECT, 2026
** main
** File description:
** Main file for the program
*/

#include <SFML/Audio/Music.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/VideoMode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graphics/engine.h"
#include "graphics/resources.h"

#include "game.h"
#include "wolf3d.h"
#include "menu.h"

static void run_game(engine_t *engine)
{
    scene_t *menu_scene = menu_create();

    if (!menu_scene) {
        fprintf(stderr, "Error: failed to create the menu scene\n");
        return;
    }
    srand(time(nullptr));
#ifndef DEBUG
    sfRenderWindow_setFramerateLimit(engine->window, FPS);
#endif
    engine_set_scene(engine, menu_scene, false);
    sfMusic_play(resources_load_music(engine->resources, MUSIC_PATH));
    engine_main_loop(engine);
    engine_destroy(engine);
}

int main(int ac, char **av, char **env)
{
    engine_t engine = {0};
    sfVideoMode video_mode = {WIN_WIDTH, WIN_HEIGHT, 32};

    if (ac == 2 && !strcmp(av[1], "-h"))
        return print_help();
    if (ac == 2 && !strcmp(av[1], "-lore"))
        return print_lore();
    if (ac != 1)
        return ERROR;
    if (!is_graphical(env)) {
        fprintf(stderr, "Error: cannot run in a non graphical environment\n");
        return ERROR;
    }
    if (!engine_init(&engine, WIN_TITLE, &video_mode, false)) {
        engine_destroy(&engine);
        fprintf(stderr, "Error: failed to initialize the engine\n");
        return ERROR;
    }
    run_game(&engine);
    return SUCCESS;
}
