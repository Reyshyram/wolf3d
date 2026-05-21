/*
** EPITECH PROJECT, 2025
** engine_main_loop.c
** File description:
** Main loop for the engine
*/

#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/View.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>
#include <stdlib.h>

#include "graphics/engine.h"
#include "graphics/maths.h"

static void transition_out(engine_t *engine)
{
    engine->transition_alpha += engine->dt / TRANSITION_SPEED;
    if (engine->transition_alpha >= 1.0F) {
        engine->transition_alpha = 1.0F;
        engine->transition_state = TRANSITION_IN;
        if (engine->scene && engine->scene->on_exit) {
            engine->scene->on_exit(engine);
            free(engine->scene);
        }
        engine->scene = engine->next_scene;
        engine->next_scene = nullptr;
        if (engine->scene && engine->scene->on_enter)
            engine->scene->on_enter(engine);
    }
}

static void transition_in(engine_t *engine)
{
    engine->transition_alpha -= engine->dt / TRANSITION_SPEED;
    if (engine->transition_alpha <= 0.0F) {
        engine->transition_alpha = 0.0F;
        engine->transition_state = TRANSITION_NONE;
        engine->next_scene = nullptr;
    }
}

static void update_transition_rect(engine_t *engine)
{
    sfColor color;

    if (engine->transition_state == TRANSITION_OUT)
        transition_out(engine);
    else if (engine->transition_state == TRANSITION_IN)
        transition_in(engine);
    color = (sfColor) {0, 0, 0, (sfUint8) (engine->transition_alpha * 255)};
    sfRectangleShape_setFillColor(engine->transition_rect, color);
}

static void handle_resize(engine_t *engine, sfEvent *event)
{
    sfView *view = sfView_create();

    engine->window_size = (sfVector2u) {event->size.width, event->size.height};
    if (engine->transition_rect)
        sfRectangleShape_setSize(engine->transition_rect,
            (sfVector2f) {(float) engine->window_size.x,
                (float) engine->window_size.y});
    sfView_reset(view,
        (sfFloatRect) {0, 0, (float) engine->window_size.x,
            (float) engine->window_size.y});
    sfRenderWindow_setView(engine->window, view);
    if (engine->scene && engine->scene->on_resize)
        engine->scene->on_resize(engine);
    sfView_destroy(view);
}

static void handle_events(engine_t *engine)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(engine->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(engine->window);
        if (event.type == sfEvtResized)
            handle_resize(engine, &event);
        if (engine->scene && engine->scene->handle_events)
            engine->scene->handle_events(engine, &event);
    }
}

void engine_main_loop(engine_t *engine)
{
    sfTime time = {0};

    while (sfRenderWindow_isOpen(engine->window)) {
        time = sfClock_restart(engine->clock);
        engine->dt =
            MIN(sfTime_asSeconds(time), (float) 0.1) * DT_SPEED_MULTIPLIER;
        if (engine->scene && engine->scene->update)
            engine->scene->update(engine);
        handle_events(engine);
        if (engine->transition_state != TRANSITION_NONE)
            update_transition_rect(engine);
        sfRenderWindow_clear(engine->window, sfBlack);
        if (engine->scene && engine->scene->data)
            engine->scene->draw(engine);
        if (engine->transition_state != TRANSITION_NONE
            && engine->transition_alpha > 0)
            sfRenderWindow_drawRectangleShape(engine->window,
                engine->transition_rect, nullptr);
        sfRenderWindow_display(engine->window);
    }
}
