#include "lvgl.h"
#include "drunkagotchi.h"
#include <stdio.h>
#include <content/character.c>
#include <content/bear.c>
#include <content/happyfood2.c>
#include <content/carrot.c>
#include <content/game.c>
#include <content/stats.c>

void event_handler(lv_event_t * e) 
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        // Get the action selected (from the event data)
        uint32_t action = (uint32_t)lv_event_get_user_data(e);
        printf("Clicked action: %lu", action);

        // Handle actions based on the button clicked
        switch (action) {
            case 0:
                printf("Feed Healthy Food\n");
                tama->full += 10;
                tama->happy += 2;  // Increase full stat
                break;
            case 1:
                printf("Feed Happy Food\n");
                tama->full += 2;
                tama->happy += 10;  // Increase happy stat
                break;
            case 2:
                printf("Train\n");
                minigame_ui(disp_global);  // Call function to play game
                break;
            case 3:
                printf("View Stats\n");
                stats_ui(disp_global, tama);  // Update UI with stats
                break;
            case 4:
                printf("Breathalyzer\n");
                // Call function to drink
                break;
            case 5:
                printf("Back to HomeScreen\n");
                homescreen_ui(disp_global);
                break;
            case 6:
                printf("Battle\n");
                //battle_ui(disp_global);
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
    int x_offset = 10; // Consistent x-offset
    int initial_offset = 30; // New vertical offset

    static lv_style_prop_t tr_prop[] = {LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_IMAGE_RECOLOR_OPA, 0};
    static lv_style_transition_dsc_t tr;
    lv_style_transition_dsc_init(&tr, tr_prop, lv_anim_path_linear, 200, 0, NULL);

    static lv_style_t style_def;
    lv_style_init(&style_def);
    lv_style_set_transition(&style_def, &tr);

    /*Darken the button when pressed and make it wider*/
    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    lv_style_set_image_recolor_opa(&style_pr, LV_OPA_30);
    lv_style_set_image_recolor(&style_pr, lv_color_black());
    lv_style_set_transform_width(&style_pr, 20);

    // Happy Food Button
    LV_IMG_DECLARE(happyfood2);
    lv_obj_t * feed_happy_btn = lv_imagebutton_create(lv_screen_active());
    lv_img_set_zoom(feed_happy_btn, .9);
    lv_imagebutton_set_src(feed_happy_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &happyfood2, NULL);
    lv_obj_add_style(feed_happy_btn, &style_def, 0);
    lv_obj_add_style(feed_happy_btn, &style_pr, LV_STATE_PRESSED);
    lv_obj_align(feed_happy_btn, LV_ALIGN_LEFT_MID, x_offset, initial_offset -button_size * 2 - button_spacing);

    // Healthy Food Button
    LV_IMG_DECLARE(carrot);
    lv_obj_t * feed_healthy_btn = lv_imagebutton_create(lv_screen_active());
    lv_imagebutton_set_src(feed_healthy_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &carrot, NULL);
    lv_obj_add_style(feed_healthy_btn, &style_def, 0);
    lv_obj_add_style(feed_healthy_btn, &style_pr, LV_STATE_PRESSED);
    lv_obj_align(feed_healthy_btn, LV_ALIGN_LEFT_MID, x_offset,  initial_offset -button_size - button_spacing / 2);

    // Games Button
    LV_IMG_DECLARE(game);
    lv_obj_t * games_btn = lv_imagebutton_create(lv_screen_active());
    lv_imagebutton_set_src(games_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &game, NULL);
    lv_image_set_src(games_btn, &game);
    lv_obj_add_style(games_btn, &style_def, 0);
    lv_obj_add_style(games_btn, &style_pr, LV_STATE_PRESSED);
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
    lv_obj_add_event_cb(battle_btn, event_handler, LV_EVENT_CLICKED, (void*)6);
}

void draw_character(lv_obj_t * parent) {
    LV_IMAGE_DECLARE(bear);
    lv_obj_t * img = lv_image_create(parent);
    lv_image_set_src(img, &bear);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void draw_right_ui(lv_obj_t * parent) {
    static lv_style_prop_t tr_prop[] = {LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_IMAGE_RECOLOR_OPA, 0};
    static lv_style_transition_dsc_t tr;
    lv_style_transition_dsc_init(&tr, tr_prop, lv_anim_path_linear, 200, 0, NULL);

    static lv_style_t style_def;
    lv_style_init(&style_def);
    lv_style_set_transition(&style_def, &tr);

    /*Darken the button when pressed and make it wider*/
    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    lv_style_set_image_recolor_opa(&style_pr, LV_OPA_30);
    lv_style_set_image_recolor(&style_pr, lv_color_black());
    lv_style_set_transform_width(&style_pr, 20);

    // Right text label
    lv_obj_t * right_label = lv_label_create(parent);
    lv_label_set_text(right_label, "Tito\n0.08");
    lv_obj_align(right_label, LV_ALIGN_RIGHT_MID, -20, -40);
    
    // Breathalyzer Button
    lv_obj_t * breath_btn = lv_btn_create(parent);
    lv_obj_set_size(breath_btn, 60, 30);
    lv_obj_add_event_cb(breath_btn, event_handler, LV_EVENT_CLICKED, (void*)4);  
    lv_obj_align(breath_btn, LV_ALIGN_RIGHT_MID, -20, 0);
    lv_obj_t * breath_label = lv_label_create(breath_btn);
    lv_label_set_text(breath_label, "Breath");
    lv_obj_center(breath_label);

    // Stats Button
    LV_IMG_DECLARE(stats);
    lv_obj_t * stats_btn = lv_imagebutton_create(lv_screen_active());
    lv_imagebutton_set_src(stats_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &stats, NULL);
    lv_obj_add_style(stats_btn, &style_def, 0);
    lv_obj_add_style(stats_btn, &style_pr, LV_STATE_PRESSED);
    //lv_obj_set_size(stats_btn, 60, 30);
    lv_obj_align(stats_btn, LV_ALIGN_RIGHT_MID, -20,  40);

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
