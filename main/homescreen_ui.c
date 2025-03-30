#include "lvgl.h"
#include "drunkagotchi.h"
#include <content/character.c>
#include <content/bear.c>
#include <content/happyfood.c>
#include <content/carrot.c>
#include <content/game.c>

void event_handler(lv_event_t * e) 
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        // Get the action selected (from the event data)
        uint32_t action = (uint32_t)lv_event_get_user_data(e);
        LV_LOG_USER("Clicked action: %u", action);

        // Handle actions based on the button clicked
        switch (action) {
            case 0:
                //social_ui(disp_global)
                break;
            case 1:
                minigame_ui(disp_global);  // Call function to play game
                break;
            case 2:
                //breathalyzer_ui(disp_global);
                // Call function to train
                break;
            case 3:
                stats_ui(disp_global, tama);  // Update UI with stats
                break;
            default:
                break;
        }
    }
}

void draw_left_ui(lv_obj_t * parent) {
    
    // UI dimensions and spacing
    int button_size = 50; // Reduced to fit screen
    int button_spacing = 10;
    int x_offset = 20; // Consistent x-offset
    int initial_offset = 30; // New vertical offset

    // Happy Food Button
    LV_IMG_DECLARE(happyfood);
    lv_obj_t * feed_happy_btn = lv_image_create(parent);
    lv_image_set_src(feed_happy_btn, &happyfood);
    lv_obj_set_size(feed_happy_btn, button_size, button_size);
    lv_obj_align(feed_happy_btn, LV_ALIGN_LEFT_MID, x_offset, initial_offset -button_size * 2 - button_spacing);

    // Healthy Food Button
    LV_IMG_DECLARE(carrot);
    lv_obj_t * feed_healthy_btn = lv_image_create(parent);
    lv_image_set_src(feed_healthy_btn, &carrot);
    lv_obj_set_size(feed_healthy_btn, button_size, button_size);
    lv_obj_align(feed_healthy_btn, LV_ALIGN_LEFT_MID, x_offset,  initial_offset -button_size - button_spacing / 2);

    // Games Button
    LV_IMG_DECLARE(game);
    lv_obj_t * games_btn = lv_image_create(parent);
    lv_image_set_src(games_btn, &game);
    lv_obj_set_size(games_btn, button_size, button_size);
    lv_obj_align(games_btn, LV_ALIGN_LEFT_MID, x_offset, initial_offset);

    // Battle Button
    lv_obj_t * battle_btn = lv_btn_create(parent);
    lv_obj_set_size(battle_btn, button_size + 10, button_size / 1.5);
    lv_obj_align(battle_btn, LV_ALIGN_LEFT_MID, x_offset, initial_offset + button_size + button_spacing / 2);
    lv_obj_t * battle_label = lv_label_create(battle_btn);
    lv_label_set_text(battle_label, "Battle");
    lv_obj_center(battle_label);

    // Event handlers
    lv_obj_add_event_cb(feed_healthy_btn, event_handler, LV_EVENT_CLICKED, (void*)0);
    lv_obj_add_event_cb(feed_happy_btn, event_handler, LV_EVENT_CLICKED, (void*)1);
    lv_obj_add_event_cb(games_btn, event_handler, LV_EVENT_CLICKED, (void*)2);
    lv_obj_add_event_cb(battle_btn, event_handler, LV_EVENT_CLICKED, (void*)3);
}

void draw_character(lv_obj_t * parent) {
    LV_IMAGE_DECLARE(bear);
    lv_obj_t * img = lv_image_create(parent);
    lv_image_set_src(img, &bear);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void draw_right_ui(lv_obj_t * parent) {
    // Right text label
    lv_obj_t * right_label = lv_label_create(parent);
    lv_label_set_text(right_label, "Tito\n0.08");
    lv_obj_align(right_label, LV_ALIGN_RIGHT_MID, -20, -40);
    
    // Breathalyzer Button
    lv_obj_t * breath_btn = lv_btn_create(parent);
    lv_obj_set_size(breath_btn, 60, 30);
    lv_obj_align(breath_btn, LV_ALIGN_RIGHT_MID, -20, 0);
    lv_obj_t * breath_label = lv_label_create(breath_btn);
    lv_label_set_text(breath_label, "Breath");
    lv_obj_center(breath_label);

    // Stats Button
    lv_obj_t * stats_btn = lv_btn_create(parent);
    lv_obj_set_size(stats_btn, 60, 30);
    lv_obj_align(stats_btn, LV_ALIGN_RIGHT_MID, -20, 40);
    lv_obj_t * stats_label = lv_label_create(stats_btn);
    lv_label_set_text(stats_label, "Stats");
    lv_obj_center(stats_label);

    lv_obj_add_event_cb(stats_btn, event_handler, LV_EVENT_CLICKED, (void*)3);  
    lv_obj_add_event_cb(breath_btn, event_handler, LV_EVENT_CLICKED, (void*)4);
}

void homescreen_ui(lv_display_t * disp)
{
    lv_obj_t * scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);

    // Left UI
    draw_left_ui(scr);

    // Toma (image)
    draw_character(scr);
    
    // Right UI
    draw_right_ui(scr);
}
