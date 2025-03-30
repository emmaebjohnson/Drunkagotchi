#include "lvgl.h"
#include "drunkagotchi.h"
#include <content/character.c>

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
    lv_obj_t * social_btn = lv_btn_create(parent);
    lv_obj_set_size(social_btn, 80, 40);
    lv_obj_align(social_btn, LV_ALIGN_LEFT_MID, 20, -60);
    lv_obj_t * social_label = lv_label_create(social_btn);
    lv_label_set_text(social_label, "Social");
    lv_obj_center(social_label);
    
    lv_obj_t * games_btn = lv_btn_create(parent);
    lv_obj_set_size(games_btn, 80, 40);
    lv_obj_align(games_btn, LV_ALIGN_LEFT_MID, 20, 0);
    lv_obj_t * games_label = lv_label_create(games_btn);
    lv_label_set_text(games_label, "Games");
    lv_obj_center(games_label);
    
    lv_obj_t * breath_btn = lv_btn_create(parent);
    lv_obj_set_size(breath_btn, 80, 40);
    lv_obj_align(breath_btn, LV_ALIGN_LEFT_MID, 20, 60);
    lv_obj_t * breath_label = lv_label_create(breath_btn);
    lv_label_set_text(breath_label, "Breathalyzer");
    lv_obj_center(breath_label);
    
    lv_obj_add_event_cb(social_btn, event_handler, LV_EVENT_CLICKED, (void*)0); 
    lv_obj_add_event_cb(games_btn, event_handler, LV_EVENT_CLICKED, (void*)1); 
    lv_obj_add_event_cb(breath_btn, event_handler, LV_EVENT_CLICKED, (void*)2);
}

void draw_character(lv_obj_t * parent) {
    LV_IMAGE_DECLARE(character);
    lv_obj_t * img = lv_image_create(parent);
    lv_image_set_src(img, &character);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void draw_right_ui(lv_obj_t * parent) {
    // Right text label
    lv_obj_t * right_label = lv_label_create(parent);
    lv_label_set_text(right_label, "Freeman\n0.08");
    lv_obj_align(right_label, LV_ALIGN_RIGHT_MID, -20, -40);
    
    // Right button
    lv_obj_t * stats_btn = lv_btn_create(parent);
    lv_obj_set_size(stats_btn, 80, 40);
    lv_obj_align(stats_btn, LV_ALIGN_RIGHT_MID, -20, 40);
    lv_obj_t * stats_label = lv_label_create(stats_btn);
    lv_label_set_text(stats_label, "Stats");
    lv_obj_center(stats_label);
    
    lv_obj_add_event_cb(stats_btn, event_handler, LV_EVENT_CLICKED, (void*)3);  // 0 for Feed Healthy
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
