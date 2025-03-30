#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lvgl.h"
#include "drunkagotchi.h"

// Function prototypes
void handle_minigame_event(lv_event_t * e);
void process_guess(int num1, int num2, char guess);

// Global variables
static int num1, num2;
static lv_style_t gradient_style;

void setup_gradient_style() {
    lv_style_init(&gradient_style);
    lv_style_set_bg_color(&gradient_style, lv_color_hex(0x7B2CBF));
    lv_style_set_bg_grad_color(&gradient_style, lv_color_hex(0x5A189A));
    lv_style_set_bg_grad_dir(&gradient_style, LV_GRAD_DIR_HOR);
    lv_style_set_radius(&gradient_style, 10);
    lv_style_set_border_width(&gradient_style, 0);
    lv_style_set_text_align(&gradient_style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_all(&gradient_style, 10);
}

void minigame_ui(lv_display_t * disp) {
    lv_obj_t * scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);

    srand((unsigned int)time(NULL) ^ (uintptr_t)&disp);
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;

    setup_gradient_style();

    lv_obj_t * label_title = lv_label_create(scr);
    lv_label_set_text(label_title, "Mini Game: Higher or Lower");
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t * label_num1 = lv_label_create(scr);
    char num1_text[32];
    snprintf(num1_text, sizeof(num1_text), "First Number: %d", num1);
    lv_label_set_text(label_num1, num1_text);
    lv_obj_align(label_num1, LV_ALIGN_TOP_MID, 0, 50);

    // Lower button (LEFT)
    lv_obj_t * btn_lower = lv_btn_create(scr);
    lv_obj_set_size(btn_lower, 100, 50);
    lv_obj_align(btn_lower, LV_ALIGN_CENTER, -80, 0);
    lv_obj_add_style(btn_lower, &gradient_style, 0);
    lv_obj_t * label_lower = lv_label_create(btn_lower);
    lv_label_set_text(label_lower, "Lower");
    lv_obj_center(label_lower);
    lv_obj_add_event_cb(btn_lower, handle_minigame_event, LV_EVENT_CLICKED, (void*)'l');

    // Higher button (RIGHT)
    lv_obj_t * btn_higher = lv_btn_create(scr);
    lv_obj_set_size(btn_higher, 100, 50);
    lv_obj_align(btn_higher, LV_ALIGN_CENTER, 80, 0);
    lv_obj_add_style(btn_higher, &gradient_style, 0);
    lv_obj_t * label_higher = lv_label_create(btn_higher);
    lv_label_set_text(label_higher, "Higher");
    lv_obj_center(label_higher);
    lv_obj_add_event_cb(btn_higher, handle_minigame_event, LV_EVENT_CLICKED, (void*)'h');

    // Back button
    lv_obj_t * btn_back = lv_btn_create(scr);
    lv_obj_set_size(btn_back, 100, 40);
    lv_obj_align(btn_back, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_style(btn_back, &gradient_style, 0);
    lv_obj_t * label_back = lv_label_create(btn_back);
    lv_label_set_text(label_back, "Back");
    lv_obj_center(label_back);
    lv_obj_add_event_cb(btn_back, event_handler, LV_EVENT_CLICKED, (void*)5);
}

void display_minigame_result(lv_display_t * disp, bool won, int actual_number) {
    lv_obj_t * scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);

    lv_obj_t * label_result = lv_label_create(scr);
    if (won) {
        lv_label_set_text(label_result, "You Won!");
    } else {
        lv_label_set_text(label_result, "You Lost!");
    }
    lv_obj_align(label_result, LV_ALIGN_CENTER, 0, -30);

    lv_obj_t * label_reveal = lv_label_create(scr);
    char reveal_text[64];
    snprintf(reveal_text, sizeof(reveal_text), "The second number was: %d", actual_number);
    lv_label_set_text(label_reveal, reveal_text);
    lv_obj_align(label_reveal, LV_ALIGN_CENTER, 0, 10);

    lv_obj_t * btn_continue = lv_btn_create(scr);
    lv_obj_set_size(btn_continue, 100, 40);
    lv_obj_align(btn_continue, LV_ALIGN_CENTER, 0, 50);
    lv_obj_add_style(btn_continue, &gradient_style, 0);
    lv_obj_t * label_continue = lv_label_create(btn_continue);
    lv_label_set_text(label_continue, "Play Again");
    lv_obj_center(label_continue);
    lv_obj_add_event_cb(btn_continue, handle_minigame_event, LV_EVENT_CLICKED, (void*)'r');
}

void handle_minigame_event(lv_event_t * e) {
    char guess = (char)(uintptr_t)lv_event_get_user_data(e);

    if (guess == 'b') {
        homescreen_ui(disp_global);
        return;
    }

    if (guess == 'r') {
        minigame_ui(disp_global);
        return;
    }

    bool won = ((guess == 'h' && num2 > num1) || (guess == 'l' && num2 < num1));
    process_guess(num1, num2, guess);

    display_minigame_result(disp_global, won, num2);

    num1 = num2;
    num2 = rand() % 100 + 1;
}

void process_guess(int num1, int num2, char guess) {
    if ((guess == 'h' && num2 > num1) || (guess == 'l' && num2 < num1)) {
        tama->trained += 10;
    } else {
        tama->trained += 5;
    }
}
