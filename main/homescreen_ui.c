#include "lvgl.h"
#include "drunkagotchi.h"
#include "drunkagotchi.c"
#include "minigame_ui.c"
#include <stdio.h>
#include <content/character.c>
#include <content/bear2.c>
#include <content/bear.c>
#include <content/happyfood2.c>
#include <content/carrot.c>
#include <content/game.c>
#include <content/stats.c>
#include <content/balance.c>

LV_IMAGE_DECLARE(bear);
 LV_IMAGE_DECLARE(bear2);
 static const lv_img_dsc_t *current_image = &bear;  // Track current image manually
 LV_IMG_DECLARE(happyfood);
 LV_IMG_DECLARE(carrot);
 LV_IMG_DECLARE(game);
 
 lv_obj_t * char_btn = NULL;

void event_handler(lv_event_t * e) 
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        // Get the action selected (from the event data)
        uint32_t action = (uint32_t)lv_event_get_user_data(e);
        printf("Clicked action: %lu\n", action);

        // Handle actions based on the button clicked
        switch (action) {
            case 0:
                printf("Feed Healthy Food\n");
                if (tama->full + 10 <= 100 && tama->happy + 2 <= 100) 
                {
                    tama->full += 10;
                    tama->happy += 2;  // Increase full stat
                }
                
                break;
            case 1:
                if(tama->happy + 10 <= 100 && tama->full + 2 <= 100)
                {
                    tama->full += 2;
                    tama->happy += 10; 
                }
                break;
            case 2:
                printf("Train\n");
                tama->state = 3;
                minigame_ui(disp_global);  // Call function to play game
                break;
            case 3:
                printf("View Stats\n");
                tama->state = 2;
                stats_ui(disp_global, tama);  // Update UI with stats
                break;
            case 4:
                printf("Breathalyzer\n");
                //replace with actual function to check BAC
                tama->BAC += 0.01f;
                tama->drunk = tama->BAC * 1000.0f;  

                if (current_image == &bear) {
                    lv_imagebutton_set_src(char_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &bear2, NULL);
                    current_image = &bear2;  // Update to new image

                } else {
                    lv_imagebutton_set_src(char_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &bear, NULL);
                    current_image = &bear;  // Update to original image
                }

                homescreen_ui(disp_global);  // Return to home screen
                break;
            case 5:
                printf("Back to HomeScreen\n");
                tama->state = 0;
                homescreen_ui(disp_global);
                
                break;
            case 6:
                printf("Battle\n");
                //battle_ui(disp_global);
                break;
            case 7:
                printf("PARTY!\n");
                
                // Button click handler
                if (current_image == &bear) {
                    lv_imagebutton_set_src(char_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &bear2, NULL);
                    current_image = &bear2;  // Update to new image
                } else {
                    lv_imagebutton_set_src(char_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &bear, NULL);
                    current_image = &bear;  // Update to original image
                }
                break;
            case 8:
                printf("Balance Game\n");
                //balance_game_ui(disp_global);
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
    lv_obj_t * feed_healthy_btn = lv_imagebutton_create(lv_screen_active());
    lv_imagebutton_set_src(feed_healthy_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &carrot, NULL);
    lv_obj_add_style(feed_healthy_btn, &style_def, 0);
    lv_obj_add_style(feed_healthy_btn, &style_pr, LV_STATE_PRESSED);
    lv_obj_align(feed_healthy_btn, LV_ALIGN_LEFT_MID, x_offset,  initial_offset -button_size - button_spacing / 2);

    // Games Button
    lv_obj_t * games_btn = lv_imagebutton_create(lv_screen_active());
    lv_imagebutton_set_src(games_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &game, NULL);
    lv_image_set_src(games_btn, &game);
    lv_obj_add_style(games_btn, &style_def, 0);
    lv_obj_add_style(games_btn, &style_pr, LV_STATE_PRESSED);
    lv_obj_align(games_btn, LV_ALIGN_LEFT_MID, x_offset, initial_offset);

    // // Battle Button
    // lv_obj_t * battle_btn = lv_btn_create(parent);
    // lv_obj_align(battle_btn, LV_ALIGN_LEFT_MID, x_offset, initial_offset + button_size + button_spacing / 2);
    // lv_obj_t * battle_label = lv_label_create(battle_btn);
    // lv_label_set_text(battle_label, "Battle");
    // lv_obj_center(battle_label);
    // Stats Button

    LV_IMG_DECLARE(balance);
    lv_obj_t * balance_btn = lv_imagebutton_create(lv_screen_active());
    lv_imagebutton_set_src(balance_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &balance, NULL);
    lv_obj_add_style(balance_btn, &style_def, 0);
    lv_obj_add_style(balance_btn, &style_pr, LV_STATE_PRESSED);
    lv_obj_align(balance_btn, LV_ALIGN_LEFT_MID, x_offset, initial_offset + button_size + button_spacing / 2);
    lv_obj_add_event_cb(balance_btn, event_handler, LV_EVENT_CLICKED, (void*)8); 

    // Event handlers
    lv_obj_add_event_cb(feed_healthy_btn, event_handler, LV_EVENT_CLICKED, (void*)0);
    lv_obj_add_event_cb(feed_happy_btn, event_handler, LV_EVENT_CLICKED, (void*)1);
    lv_obj_add_event_cb(games_btn, event_handler, LV_EVENT_CLICKED, (void*)2);
    lv_obj_add_event_cb(balance_btn, event_handler, LV_EVENT_CLICKED, (void*)8);
}

void draw_character(lv_obj_t * parent) {

    char_btn = lv_imagebutton_create(parent);
    lv_imagebutton_set_src(char_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &bear, NULL);
    lv_obj_align(char_btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(char_btn, event_handler, LV_EVENT_CLICKED, (void*)7);
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

    // BAC Display (Larger & Variable)
    lv_obj_t * right_label = lv_label_create(parent);
    char bac_text[32];
    snprintf(bac_text, sizeof(bac_text), "Tito\nBAC: %.2f", tama->BAC);
    lv_label_set_text(right_label, bac_text);
    lv_obj_set_style_text_font(right_label, &lv_font_montserrat_14, 0); // Larger Font
    lv_obj_align(right_label, LV_ALIGN_RIGHT_MID, -20, -70);

    // Breathalyzer Button (More Spacing)
    lv_obj_t * breath_btn = lv_btn_create(parent);
    lv_obj_set_size(breath_btn, 80, 40); // Larger button
    lv_obj_add_event_cb(breath_btn, event_handler, LV_EVENT_CLICKED, (void*)4);
    lv_obj_align(breath_btn, LV_ALIGN_RIGHT_MID, -20, -10); // Lowered
    lv_obj_t * breath_label = lv_label_create(breath_btn);
    lv_label_set_text(breath_label, "Get BAC");
    lv_obj_center(breath_label);

    // Battle Button
    // lv_obj_t * battle_btn = lv_btn_create(parent);
    // lv_obj_set_size(battle_btn, 60, 30);
    // lv_obj_align(battle_btn, LV_ALIGN_RIGHT_MID, -20,  55);
    // lv_obj_t * battle_label = lv_label_create(battle_btn);
    // lv_label_set_text(battle_label, "Battle");
    // lv_obj_center(battle_label);
    // lv_obj_add_event_cb(battle_btn, event_handler, LV_EVENT_CLICKED, (void*)6); 


    // Stats Button
    LV_IMG_DECLARE(stats);
    lv_obj_t * stats_btn = lv_imagebutton_create(lv_screen_active());
    lv_imagebutton_set_src(stats_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &stats, NULL);
    lv_obj_add_style(stats_btn, &style_def, 0);
    lv_obj_add_style(stats_btn, &style_pr, LV_STATE_PRESSED);
    //lv_obj_set_size(stats_btn, 60, 30);
    lv_obj_align(stats_btn, LV_ALIGN_RIGHT_MID, -20,  55);
    lv_obj_add_event_cb(stats_btn, event_handler, LV_EVENT_CLICKED, (void*)3); 
}

void homescreen_ui(lv_display_t * disp)
{
    tama->state = 1;
    lv_obj_t * scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);

    // Left UI
    draw_left_ui(scr);

    // Toma (image)
    draw_character(scr);
    
    // Right UI
    draw_right_ui(scr);
}
