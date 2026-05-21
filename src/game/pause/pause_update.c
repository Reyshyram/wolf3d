/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_update
*/

#include <stdlib.h>
#include "graphics/engine.h"
#include "graphics/ui.h"
#include "game.h"

static void pause_update_settings(engine_t *engine, game_data_t *d)
{
    if (d->pause.page == PAUSE_PAGE_CONTROLS) {
        ui_button_update(engine, d->pause.controls_move);
        ui_button_update(engine, d->pause.win_mode);
    }
    if (d->pause.page == PAUSE_PAGE_SOUNDS) {
        ui_button_update(engine, d->pause.sound_master);
        ui_button_update(engine, d->pause.sound_steps);
    }
    if (d->pause.page == PAUSE_PAGE_HUD) {
        ui_button_update(engine, d->pause.hud_minimap);
        ui_button_update(engine, d->pause.hud_timer);
    }
}

void pause_update(engine_t *engine, game_data_t *d)
{
    if (!d)
        return;
    if (d->pause.page == PAUSE_PAGE_MAIN) {
        ui_button_update(engine, d->pause.resume);
        ui_button_update(engine, d->pause.save);
        ui_button_update(engine, d->pause.exit);
        ui_button_update(engine, d->pause.controls);
        ui_button_update(engine, d->pause.sounds);
        ui_button_update(engine, d->pause.hud);
    } else {
        pause_update_settings(engine, d);
    }
}
