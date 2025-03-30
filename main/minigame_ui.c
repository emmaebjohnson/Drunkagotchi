#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lvgl.h"
#include "drunkagotchi.h"

// Function prototypes
void handle_minigame_event(lv_event_t * e);
void minigame_ui(lv_display_t * disp);
void process_guess(int num1, int num2, char guess);

static int num1, num2;
static int battle_points = 0;

void minigame_ui(lv_display_t * disp) {
    lv_obj_t * scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);

    srand((unsigned int)time(NULL) ^ (uintptr_t)&disp);
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;

    lv_obj_t * label_title = lv_label_create(scr);
    lv_label_set_text(label_title, "Mini Game: Higher or Lower");
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t * label_num1 = lv_label_create(scr);
    char num1_text[32];
    snprintf(num1_text, sizeof(num1_text), "First Number: %d", num1);
    lv_label_set_text(label_num1, num1_text);
    lv_obj_align(label_num1, LV_ALIGN_TOP_MID, 0, 50);

    lv_obj_t * btn_higher = lv_btn_create(scr);
    lv_obj_align(btn_higher, LV_ALIGN_CENTER, -60, 0);
    lv_obj_t * label_higher = lv_label_create(btn_higher);
    lv_label_set_text(label_higher, "Higher");
    lv_obj_add_event_cb(btn_higher, handle_minigame_event, LV_EVENT_CLICKED, (void*)'h');

    lv_obj_t * btn_lower = lv_btn_create(scr);
    lv_obj_align(btn_lower, LV_ALIGN_CENTER, 60, 0);
    lv_obj_t * label_lower = lv_label_create(btn_lower);
    lv_label_set_text(label_lower, "Lower");
    lv_obj_add_event_cb(btn_lower, handle_minigame_event, LV_EVENT_CLICKED, (void*)'l');

    lv_obj_t * btn_back = lv_btn_create(scr);
    lv_obj_align(btn_back, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t * label_back = lv_label_create(btn_back);
    lv_label_set_text(label_back, "Back");
    lv_obj_add_event_cb(btn_back, handle_minigame_event, LV_EVENT_CLICKED, (void*)'b');
}

void handle_minigame_event(lv_event_t * e) {
    char guess = (char)(uintptr_t)lv_event_get_user_data(e);

    if (guess == 'b') {
        drunkagotchi_ui(disp_global);
        return;
    }

    process_guess(num1, num2, guess);
    num1 = num2;
    num2 = rand() % 100 + 1;

    minigame_ui(disp_global);
}

void process_guess(int num1, int num2, char guess) {
    if ((guess == 'h' && num2 > num1) || (guess == 'l' && num2 < num1)) {
        tama->trained += 10;
    } else {
        tama->trained += 5;
    }
}
