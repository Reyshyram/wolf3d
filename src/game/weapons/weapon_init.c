/*
** EPITECH PROJECT, 2026
** weapon_init.c
** File description:
** Init weapons
*/

#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>

#include "graphics/engine.h"
#include "graphics/resources.h"

#include "game.h"
#include "weapons.h"
#include "wolf3d.h"

static const weapon_info_t WEAPON_CONFIGS[WEAPON_TYPE_COUNT] = {
    {AK_AMMO, AK_FIRE_COOLDOWN, AK_RELOAD_TIME, AK_RECOIL, true, AK_UI_PATH,
        AK_HELD_PATH, SHOT_SFX_PATH},
    {BAZOOKA_AMMO, BAZOOKA_FIRE_COOLDOWN, BAZOOKA_RELOAD_TIME, BAZOOKA_RECOIL,
        false, BAZOOKA_UI_PATH, BAZOOKA_HELD_PATH, LASER_SFX_PATH},
    {REVOLVER_AMMO, REVOLVER_FIRE_COOLDOWN, REVOLVER_RELOAD_TIME,
        REVOLVER_RECOIL, false, REVOLVER_UI_PATH, REVOLVER_HELD_PATH,
        SHOT_SFX_PATH},
    {GRENADE_AMMO, GRENADE_FIRE_COOLDOWN, 0, GRENADE_RECOIL, false,
        GRENADE_UI_PATH, GRENADE_HELD_PATH, GRENADE_SFX_PATH},
};

static void scale_sprite(sfSprite *sprite, sfTexture *tex, float height)
{
    sfVector2u size = sfTexture_getSize(tex);
    float scale = height / (float) size.y;

    sfSprite_setScale(sprite, (sfVector2f) {scale, scale});
    sfSprite_setOrigin(sprite,
        (sfVector2f) {(float) size.x / 2.0F, (float) size.y / 2.0F});
}

static bool load_sprites(engine_t *engine, weapon_t *w)
{
    w->ui_texture = resources_load_texture(engine->resources,
        w->weapon_data->ui_sprite_path);
    w->held_texture = resources_load_texture(engine->resources,
        w->weapon_data->held_sprite_path);
    if (!w->ui_texture || !w->held_texture)
        return false;
    w->ui_sprite = sfSprite_create();
    w->held_sprite = sfSprite_create();
    if (!w->ui_sprite || !w->held_sprite)
        return false;
    sfSprite_setTexture(w->ui_sprite, w->ui_texture, true);
    sfSprite_setTexture(w->held_sprite, w->held_texture, true);
    scale_sprite(w->ui_sprite, w->ui_texture, HUD_WEAPON_HEIGHT);
    scale_sprite(w->held_sprite, w->held_texture,
        (float) WIN_HEIGHT * WEAPON_HEIGHT);
    return true;
}

static void set_weapon_stats(weapon_t *w, weapon_type_t type)
{
    w->type = type;
    w->weapon_data = &WEAPON_CONFIGS[type];
    w->ammo = w->weapon_data->max_ammo;
}

static bool init_weapon(engine_t *engine, weapon_t *w, weapon_type_t type)
{
    set_weapon_stats(w, type);
    w->shoot_sound = resources_load_sound(engine->resources,
        w->weapon_data->shoot_sfx_path);
    w->reload_sound = resources_load_sound(engine->resources, RELOAD_SFX_PATH);
    return load_sprites(engine, w);
}

int init_weapons(engine_t *engine, game_data_t *data, weapon_type_t main_type)
{
    if (!init_weapon(engine, &data->weapons[WEAPON_SLOT_MAIN], main_type))
        return ERROR;
    if (!init_weapon(engine, &data->weapons[WEAPON_SLOT_GRENADE],
            WEAPON_GRENADE))
        return ERROR;
    data->active_weapon = WEAPON_SLOT_MAIN;
    return SUCCESS;
}
