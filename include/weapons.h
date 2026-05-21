/*
** EPITECH PROJECT, 2026
** weapons.h
** File description:
** weapons header
*/

#ifndef WEAPONS_H
// clang-format off
    #define WEAPONS_H

    #include <SFML/Audio/Types.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>

    #include "graphics/engine.h"

    #define SHOT_SFX_PATH SFXS_PATHS "gun/shot.mp3"
    #define LASER_SFX_PATH SFXS_PATHS "gun/laser.mp3"
    #define GRENADE_SFX_PATH SFXS_PATHS "gun/grenade.mp3"
    #define RELOAD_SFX_PATH SFXS_PATHS "gun/reload.mp3"

    #define AK_UI_PATH SPRITES_PATH "weapons/ak.png"
    #define AK_HELD_PATH SPRITES_PATH "weapons/ak_held.png"
    #define BAZOOKA_UI_PATH SPRITES_PATH "weapons/bazooka.png"
    #define BAZOOKA_HELD_PATH SPRITES_PATH "weapons/bazooka_held.png"
    #define REVOLVER_UI_PATH SPRITES_PATH "weapons/revolver.png"
    #define REVOLVER_HELD_PATH SPRITES_PATH "weapons/revolver_held.png"
    #define GRENADE_UI_PATH SPRITES_PATH "weapons/grenade.png"
    #define GRENADE_HELD_PATH SPRITES_PATH "weapons/grenade_held.png"

    #define HUD_BASE_WIDTH 1920.0F
    #define HUD_BASE_HEIGHT 1080.0F
    #define HUD_WEAPON_HEIGHT (engine->window_size.y * (80.F / HUD_BASE_HEIGHT))
    #define HUD_AMMO_SIZE 36
    #define HUD_AMMO_ICON_HEIGHT 64
    #define HUD_INACTIVE_SCALE 0.65F
    #define HUD_WEAPON_GAP_X 80.0F
    #define HUD_WEAPON_GAP_Y 70.0F
    #define HUD_ICON_GAP 32.0F
    #define HUD_TEXT_ROW_GAP 18.0F
    #define HUD_TEXT_ICON_GAP 10.0F
    #define AMMO_ICON_PATH SPRITES_PATH "weapons/ammo.png"
    #define HUD_SCALE_W ((float) engine->window_size.x / HUD_BASE_WIDTH)
    #define HUD_SCALE_H ((float) engine->window_size.y / HUD_BASE_HEIGHT)
    #define HUD_SCALE (HUD_SCALE_W < HUD_SCALE_H ? HUD_SCALE_W : HUD_SCALE_H)

    #define WEAPON_SLOT_MAIN 0
    #define WEAPON_SLOT_GRENADE 1
    #define WEAPON_SLOT_COUNT 2

    #define AK_AMMO 30
    #define AK_FIRE_COOLDOWN 0.1F
    #define AK_RELOAD_TIME 2.0F
    #define AK_RECOIL 65.0F

    #define BAZOOKA_AMMO 5
    #define BAZOOKA_FIRE_COOLDOWN 2.0F
    #define BAZOOKA_RELOAD_TIME 4.0F
    #define BAZOOKA_RECOIL 380.0F

    #define REVOLVER_AMMO 6
    #define REVOLVER_FIRE_COOLDOWN 0.5F
    #define REVOLVER_RELOAD_TIME 1.5F
    #define REVOLVER_RECOIL 125.0F

    #define GRENADE_AMMO 3
    #define GRENADE_FIRE_COOLDOWN 1.2F
    #define GRENADE_RECOIL 260.0F

    #define RECOIL_SPEED 3.0F
    #define SHOOT_ANIM_DURATION 0.15F
    #define RELOAD_ANIM_TIME 0.25F
    #define WEAPON_HEIGHT 0.55F
    #define WEAPON_POS_X (engine->window_size.x * 0.70F)
    #define WEAPON_POS_Y (engine->window_size.y * 0.80F)
    #define SHOOT_OFFSET_Y 70.0F
    #define SHOOT_OFFSET_X 25.0F

    #define DEFAULT_MAIN_WEAPON WEAPON_BAZOOKA
// clang-format on

typedef enum {
    WEAPON_AK,
    WEAPON_BAZOOKA,
    WEAPON_REVOLVER,
    WEAPON_GRENADE,
    WEAPON_TYPE_COUNT
} weapon_type_t;

typedef struct {
    int max_ammo;
    float fire_cooldown;
    float reload_time;
    float recoil;
    bool is_auto;
    const char *ui_sprite_path;
    const char *held_sprite_path;
    const char *shoot_sfx_path;
} weapon_info_t;

typedef struct {
    const weapon_info_t *weapon_data;
    sfSprite *ui_sprite;
    sfTexture *ui_texture;
    sfSprite *held_sprite;
    sfTexture *held_texture;
    sfSound *shoot_sound;
    sfSound *reload_sound;
    weapon_type_t type;
    int ammo;
    float reload_timer;
    float shoot_cooldown;
    float shoot_anim_timer;
    bool is_reloading;
} weapon_t;

typedef struct game_s game_data_t;

int init_weapons(engine_t *engine, game_data_t *data, weapon_type_t main_type);
void resize_weapons(engine_t *engine, game_data_t *data);
void free_weapons(game_data_t *data);
void update_weapons(engine_t *engine, game_data_t *d);
void draw_weapon(engine_t *engine, game_data_t *d);
void draw_weapon_hud(engine_t *engine, game_data_t *d);
bool weapon_shoot(game_data_t *d);
void weapon_reload(game_data_t *d);
void weapon_change(game_data_t *d);

#endif /* !WEAPONS_H */
