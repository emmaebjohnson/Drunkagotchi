#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "lvgl.h"
#include "drunkagotchi.h"

// Function prototypes
void handle_minigame_event(lv_event_t * e);
static void balance_timer_cb(lv_timer_t * timer);
void draw_buttons(lv_obj_t * parent);
void draw_game(lv_obj_t * parent);
void balance_game_ui(lv_display_t * disp);
void minigame_result(lv_display_t * disp);

// Global variables
static lv_style_t gradient_style;
LV_IMAGE_DECLARE(bear);
lv_obj_t * player = NULL;
static float angle = 1;
static float angular_velocity = 0;  
static const float damping = 0.98;  

void game_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        uint32_t action = (uint32_t)lv_event_get_user_data(e);
        printf("Clicked action: %lu\n", action);
        
        switch (action) {
            case 0:
                printf("Left Pressed\n");
                angle += 10;  // Reduced angle step for better control
                break;
            case 1:
                printf("Right Pressed\n");
                angle -= 10;
                break;
            case 2:
                printf("Restart\n");
                balance_game_ui(disp_global);
                break;
            default:
                break;
        }
        lv_img_set_angle(player, (int)(angle * 10));
    }
}

void draw_buttons(lv_obj_t * parent) {
    lv_obj_t * left_btn = lv_btn_create(parent);
    lv_obj_set_size(left_btn, 80, 40); 
    lv_obj_align(left_btn, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_add_event_cb(left_btn, game_handler, LV_EVENT_CLICKED, (void*)0);
    lv_obj_t * left_label = lv_label_create(left_btn);
    lv_label_set_text(left_label, "Left");
    lv_obj_center(left_label);

    lv_obj_t * right_btn = lv_btn_create(parent);
    lv_obj_set_size(right_btn, 80, 40); 
    lv_obj_align(right_btn, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_event_cb(right_btn, game_handler, LV_EVENT_CLICKED, (void*)1);
    lv_obj_t * right_label = lv_label_create(right_btn);
    lv_label_set_text(right_label, "Right");
    lv_obj_center(right_label);
    
    // Back Button
    lv_obj_t * back_btn = lv_btn_create(parent);  
    lv_obj_set_size(back_btn, 70, 30);
    lv_obj_add_event_cb(back_btn, event_handler, LV_EVENT_CLICKED, (void*)5);  
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_remove_flag(back_btn, LV_OBJ_FLAG_PRESS_LOCK);
    
    lv_obj_t * label = lv_label_create(back_btn);
    lv_label_set_text(label, "Back");
    lv_obj_center(label);
}

void draw_game(lv_obj_t * parent) {
    player = lv_img_create(parent);
    lv_img_set_src(player, &bear);
    lv_obj_align(player, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_angle(player, (int)(angle * 10));
}

static void balance_timer_cb(lv_timer_t * timer) {
    if (angle <= -45 || angle >= 45) {
        printf("Game Over! Angle out of bounds.\n");
        lv_timer_del(timer); 
        minigame_result(disp_global);  
        return;
    }

    // Simulate physics-based movement
    float gravity_force = -9.8 * sin(angle * (M_PI / 180.0));  
    angular_velocity += gravity_force * 0.1;  
    angular_velocity *= damping;  
    angle += angular_velocity;  

    lv_img_set_angle(player, (int)(angle * 10));  
}

void balance_game_ui(lv_display_t * disp) {
    lv_obj_t * scr = lv_disp_get_scr_act(disp);
    lv_obj_clean(scr);
    draw_buttons(scr);
    draw_game(scr);
    
    // Start the balance physics timer
    lv_timer_create(balance_timer_cb, 30, NULL);
}

void minigame_result(lv_display_t * disp) {
    lv_obj_t * scr = lv_disp_get_scr_act(disp);
    lv_obj_clean(scr);
    
    angle = 1;

    lv_obj_t * label_result = lv_label_create(scr);
    lv_label_set_text(label_result, "You Win!");
    lv_obj_align(label_result, LV_ALIGN_CENTER, 0, -30);

    lv_obj_t * btn_continue = lv_btn_create(scr);
    lv_obj_set_size(btn_continue, 100, 40);
    lv_obj_align(btn_continue, LV_ALIGN_CENTER, 0, 50);
    lv_obj_add_style(btn_continue, &gradient_style, 0);
    lv_obj_t * label_continue = lv_label_create(btn_continue);
    lv_label_set_text(label_continue, "Play Again");
    lv_obj_center(label_continue);
    lv_obj_add_event_cb(btn_continue, game_handler, LV_EVENT_CLICKED, (void*)2);
}
