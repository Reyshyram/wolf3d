/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** pause_create
*/

#include "game.h"
#include "graphics/engine.h"
#include "graphics/resources.h"
#include "graphics/ui.h"
#include "menu.h"
#include "wolf3d.h"

static ui_button_t *create_btn(engine_t *engine, const char *tex,
    sfVector2f *pos)
{
    sfVector2f size = {220.0F, 60.0F};
    sfVector2u text_size;

    if (tex) {
        text_size =
            sfTexture_getSize(resources_load_texture(engine->resources, tex));
        size.y = size.x * (float) text_size.y / (float) text_size.x;
    }
    return ui_button_create(engine, tex, pos, &size);
}

static void destroy_text_btn(ui_button_t *button)
{
    if (button->background)
        sfRectangleShape_destroy(button->background);
    if (button->text)
        sfText_destroy(button->text);
    free(button);
}

static ui_button_t *create_text_btn(engine_t *engine, sfVector2f *pos,
    sfVector2f *size, const char *label)
{
    ui_button_t *button = calloc(1, sizeof(*button));
    sfColor color = sfWhite;

    if (!button)
        return nullptr;
    button->background = sfRectangleShape_create();
    button->text = sfText_create();
    if (!button->background || !button->text) {
        destroy_text_btn(button);
        return nullptr;
    }
    sfRectangleShape_setPosition(button->background, *pos);
    sfRectangleShape_setSize(button->background, *size);
    sfRectangleShape_setFillColor(button->background,
        sfColor_fromRGBA(0, 0, 0, 40));
    sfRectangleShape_setTexture(button->background, nullptr, sfTrue);
    sfText_setFont(button->text, engine->default_font);
    button->scale = (sfVector2f) {1, 1};
    button->char_size = 14;
    ui_button_set_text(button, label, 14, &color);
    return button;
}

static void init_setting_btn(ui_button_t *button, engine_t *engine,
    void (*on_click)(void *), const char *label)
{
    sfColor color = sfWhite;

    if (!button)
        return;
    ui_button_set_text(button, label, 14, &color);
    button->on_click = on_click;
    button->data = engine;
}

static void init_pause_bg(engine_t *engine, pause_menu_t *pause)
{
    sfTexture *texture = resources_load_texture(engine->resources,
        "assets/sprites/main_menu/bg_menu_pause.png");
    sfVector2u text_size = sfTexture_getSize(texture);
    sfColor line_c = {0, 0, 0, 100};

    pause->bg = sfSprite_create();
    sfSprite_setTexture(pause->bg, texture, sfTrue);
    sfSprite_setScale(pause->bg,
        (sfVector2f) {(float) WIN_WIDTH / (float) text_size.x,
            (float) WIN_HEIGHT / (float) text_size.y});
    pause->separator = sfRectangleShape_create();
    sfRectangleShape_setSize(pause->separator, (sfVector2f) {4.0F, 500.0F});
    sfRectangleShape_setFillColor(pause->separator, line_c);
    sfRectangleShape_setOrigin(pause->separator, (sfVector2f) {2.0F, 250.0F});
    sfRectangleShape_setPosition(pause->separator,
        (sfVector2f) {WIN_WIDTH / 2.0F, WIN_HEIGHT / 2.0F});
}

static void init_main_left(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f left = {WIN_WIDTH / 2.0F - 250.0F, WIN_HEIGHT / 2.0F - 100.0F};

    pause->resume = create_btn(engine,
        "assets/sprites/main_menu/button_resume.png", &left);
    pause->resume->on_click = &pause_on_resume;
    pause->resume->data = engine;
    left.y += 100.0F;
    pause->save = create_btn(engine,
        "assets/sprites/main_menu/button_save.png", &left);
    pause->save->on_click = &pause_on_save;
    pause->save->data = engine;
    left.y += 100.0F;
    pause->exit = create_btn(engine,
        "assets/sprites/main_menu/button_exit.png", &left);
    pause->exit->on_click = &pause_on_exit;
    pause->exit->data = engine;
}

static void init_main_right(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f right = {WIN_WIDTH / 2.0F + 250.0F,
        WIN_HEIGHT / 2.0F - 100.0F};

    pause->controls = create_btn(engine,
        "assets/sprites/main_menu/button_keys.png", &right);
    pause->controls->on_click = &pause_on_controls;
    pause->controls->data = engine;
    right.y += 100.0F;
    pause->sounds = create_btn(engine,
        "assets/sprites/main_menu/button_sounds.png", &right);
    pause->sounds->on_click = &pause_on_sounds;
    pause->sounds->data = engine;
    right.y += 100.0F;
    pause->hud = create_btn(engine,
        "assets/sprites/main_menu/button_params.png", &right);
    pause->hud->on_click = &pause_on_hud;
    pause->hud->data = engine;
}

static void init_controls_page(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f size = {180.0F, 48.0F};
    sfVector2f left = {WIN_WIDTH / 2.0F - 230.0F, WIN_HEIGHT / 2.0F - 60.0F};
    sfVector2f right = {WIN_WIDTH / 2.0F + 230.0F,
        WIN_HEIGHT / 2.0F - 60.0F};
    sfVector2f bottom = {WIN_WIDTH / 2.0F, WIN_HEIGHT / 2.0F + 50.0F};

    pause->controls_move = create_text_btn(engine, &left, &size, "ZQSD / WASD");
    pause->controls_camera = create_text_btn(engine, &right, &size, "Souris");
    pause->controls_pause = create_text_btn(engine, &bottom, &size, "Echap");
}

static void init_sounds_page(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f size = {220.0F, 48.0F};
    sfVector2f master = {WIN_WIDTH / 2.0F, WIN_HEIGHT / 2.0F - 40.0F};
    sfVector2f steps = {WIN_WIDTH / 2.0F, WIN_HEIGHT / 2.0F + 70.0F};

    pause->sound_master = create_text_btn(engine, &master, &size, "Sons");
    pause->sound_steps = create_text_btn(engine, &steps, &size, "Pas");
    init_setting_btn(pause->sound_master, engine, &pause_on_sound_master,
        "Sons: ON");
    init_setting_btn(pause->sound_steps, engine, &pause_on_sound_steps,
        "Pas: ON");
}

static void init_hud_page(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f size = {220.0F, 48.0F};
    sfVector2f minimap = {WIN_WIDTH / 2.0F, WIN_HEIGHT / 2.0F - 40.0F};
    sfVector2f timer = {WIN_WIDTH / 2.0F, WIN_HEIGHT / 2.0F + 70.0F};

    pause->hud_minimap = create_text_btn(engine, &minimap, &size, "Mini-map");
    pause->hud_timer = create_text_btn(engine, &timer, &size, "Timer");
    init_setting_btn(pause->hud_minimap, engine, &pause_on_hud_minimap,
        "Mini-map: ON");
    init_setting_btn(pause->hud_timer, engine, &pause_on_hud_timer,
        "Timer: ON");
}

static void init_back_button(engine_t *engine, pause_menu_t *pause)
{
    sfVector2f back = {150.0F, 90.0F};
    sfVector2f size = {150.0F, 44.0F};

    pause->back = create_text_btn(engine, &back, &size, "Retour");
    pause->back->on_click = &pause_on_back;
    pause->back->data = engine;
}

void pause_init(engine_t *engine, game_data_t *data)
{
    init_pause_bg(engine, &data->pause);
    init_back_button(engine, &data->pause);
    init_main_left(engine, &data->pause);
    init_main_right(engine, &data->pause);
    init_controls_page(engine, &data->pause);
    init_sounds_page(engine, &data->pause);
    init_hud_page(engine, &data->pause);
    data->pause.page = PAUSE_PAGE_MAIN;
}
