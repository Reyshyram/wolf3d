/*
** EPITECH PROJECT, 2026
** game_update.c
** File description:
** Update the game
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>
#include <math.h>

#include "graphics/engine.h"

#include "game.h"
#include "wolf3d.h"

#ifdef DEBUG

    #include <SFML/System/Clock.h>
    #include <SFML/System/Time.h>
    #include <SFML/System/Types.h>

    #include <stdio.h>

void print_framerate()
{
    static int first = 1;
    static sfClock *clock;
    static int fps = 0;

    if (first == 1) {
        clock = sfClock_create();
        first = 0;
    }
    sfTime elapsed = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed) >= 1) {
        printf(" %3d FPS\n", fps);
        fflush(stdout);
        fps = 0;
        sfClock_restart(clock);
    } else
        fps++;
}
#endif

static void rotate_camera(game_data_t *d, float angle)
{
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    float prev_dir_x = d->player.view_dir.x;
    float prev_plane_x = d->camera_plane.x;

    d->player.view_dir.x = prev_dir_x * cos_a - d->player.view_dir.y * sin_a;
    d->player.view_dir.y = prev_dir_x * sin_a + d->player.view_dir.y * cos_a;
    d->camera_plane.x = prev_plane_x * cos_a - d->camera_plane.y * sin_a;
    d->camera_plane.y = prev_plane_x * sin_a + d->camera_plane.y * cos_a;
}

static void move_player(game_data_t *d, float dx, float dy)
{
    float new_x = d->player.pos.x + dx;
    float new_y = d->player.pos.y + dy;
    float pos_x = d->player.pos.x;
    float pos_y = d->player.pos.y;
    float margin = COLLISION_MARGIN;

    if (d->map[(int) (new_x + margin)][(int) (pos_y + margin)] == 0
        && d->map[(int) (new_x + margin)][(int) (pos_y - margin)] == 0
        && d->map[(int) (new_x - margin)][(int) (pos_y + margin)] == 0
        && d->map[(int) (new_x - margin)][(int) (pos_y - margin)] == 0)
        d->player.pos.x = new_x;
    if (d->map[(int) (pos_x + margin)][(int) (new_y + margin)] == 0
        && d->map[(int) (pos_x - margin)][(int) (new_y + margin)] == 0
        && d->map[(int) (pos_x + margin)][(int) (new_y - margin)] == 0
        && d->map[(int) (pos_x - margin)][(int) (new_y - margin)] == 0)
        d->player.pos.y = new_y;
}

static void handle_camera_movement(game_data_t *d, engine_t *engine)
{
    sfVector2i center = {WIN_WIDTH / 2, WIN_HEIGHT / 2};
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(engine->window);
    int mouse_dx = mouse_pos.x - center.x;
    int mouse_dy = mouse_pos.y - center.y;

    sfMouse_setPositionRenderWindow(center, engine->window);
    if (mouse_dx != 0)
        rotate_camera(d, -(float) mouse_dx * MOUSE_X_SENSITIVITY);
    if (mouse_dy != 0)
        d->camera_height -= (float) mouse_dy * MOUSE_Y_SENSITIVITY;
    if (d->camera_height > (float) WIN_HEIGHT / 2 - 1)
        d->camera_height = (float) WIN_HEIGHT / 2 - 1;
    if (d->camera_height < -(float) WIN_HEIGHT / 2 + 1)
        d->camera_height = -(float) WIN_HEIGHT / 2 + 1;
}

static sfVector2f get_normalized_movement(float dt, sfVector2f *dir)
{
    float move_speed = dt * MOVE_SPEED;
    float len = hypotf(dir->x, dir->y);

    if (len > 0) {
        dir->x = dir->x / len * move_speed;
        dir->y = dir->y / len * move_speed;
    }
    return *dir;
}

static sfVector2f get_player_movement(float dt, game_data_t *d)
{
    sfVector2f dir = {0};

    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        dir.x += d->player.view_dir.x;
        dir.y += d->player.view_dir.y;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        dir.x -= d->player.view_dir.x;
        dir.y -= d->player.view_dir.y;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        dir.x += -d->player.view_dir.y;
        dir.y += d->player.view_dir.x;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        dir.x += d->player.view_dir.y;
        dir.y += -d->player.view_dir.x;
    }
    return get_normalized_movement(dt, &dir);
}

void game_update(engine_t *engine)
{
    game_data_t *d = (game_data_t *) engine->scene->data;
    sfVector2f movement = {0};
    float speed_mult = 1;

    if (!d)
        return;
#ifdef DEBUG
    print_framerate();
#endif
    handle_camera_movement(d, engine);
    movement = get_player_movement(engine->dt, d);
    if (sfKeyboard_isKeyPressed(sfKeyLShift))
        speed_mult = SPRINT_MULT;
    else if (sfKeyboard_isKeyPressed(sfKeyLControl))
        speed_mult = CROUCH_MULT;
    if (movement.x != 0 || movement.y != 0)
        move_player(d, movement.x * speed_mult, movement.y * speed_mult);
}
