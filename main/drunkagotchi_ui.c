#include "lvgl.h"
#include <stdio.h>

static void button_event_cb(lv_event_t * e)
{
    uint32_t btn_id = lv_buttonmatrix_get_selected_button(lv_event_get_target_obj(e));
    switch(btn_id) {
        case 0: 
            printf("Feed Healthy Food\n"); 
            break;
        case 1: 
            printf("Feed Happy Food\n"); 
            break;
        case 2: 
            printf("Train\n"); 
            break;
        case 3: 
            printf("View Stats\n"); 
            break;
        case 4: 
            printf("Drink\n"); 
            break;
        default: 
            break;
    }
}

void drunkagotchi_ui(lv_display_t * disp)
{
    lv_obj_t * scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);

    // Main container (horizontal layout)
    lv_obj_t * container = lv_obj_create(scr);
    lv_obj_set_size(container, 240, 320); // Adapt to your screen size
    lv_obj_center(container);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);

    // Side button container
    lv_obj_t * btn_container = lv_obj_create(container);
    lv_obj_set_size(btn_container, 80, 320);
    lv_obj_set_flex_flow(btn_container, LV_FLEX_FLOW_COLUMN);

    // Icon-only buttons using LVGL symbols
    lv_obj_t * btn_feed_healthy = lv_btn_create(btn_container);
    lv_obj_set_size(btn_feed_healthy, 64, 64);
    lv_obj_t * label1 = lv_label_create(btn_feed_healthy);
    lv_label_set_text(label1, LV_SYMBOL_EYE_OPEN); // Heart symbol
    lv_obj_center(label1);

    lv_obj_t * btn_feed_happy = lv_btn_create(btn_container);
    lv_obj_set_size(btn_feed_happy, 64, 64);
    lv_obj_t * label2 = lv_label_create(btn_feed_happy);
    lv_label_set_text(label2, LV_SYMBOL_HOME); // Home symbol
    lv_obj_center(label2);

    lv_obj_t * btn_train = lv_btn_create(btn_container);
    lv_obj_set_size(btn_train, 64, 64);
    lv_obj_t * label3 = lv_label_create(btn_train);
    lv_label_set_text(label3, LV_SYMBOL_PLAY); // Play symbol
    lv_obj_center(label3);

    lv_obj_t * btn_stats = lv_btn_create(btn_container);
    lv_obj_set_size(btn_stats, 64, 64);
    lv_obj_t * label4 = lv_label_create(btn_stats);
    lv_label_set_text(label4, LV_SYMBOL_LIST); // List symbol
    lv_obj_center(label4);

    lv_obj_t * btn_drink = lv_btn_create(btn_container);
    lv_obj_set_size(btn_drink, 64, 64);
    lv_obj_t * label5 = lv_label_create(btn_drink);
    lv_label_set_text(label5, LV_SYMBOL_BATTERY_1); // Droplet symbol
    lv_obj_center(label5);

    // Event listeners
    lv_obj_add_event_cb(btn_feed_healthy, button_event_cb, LV_EVENT_CLICKED, (void*)0);
    lv_obj_add_event_cb(btn_feed_happy, button_event_cb, LV_EVENT_CLICKED, (void*)1);
    lv_obj_add_event_cb(btn_train, button_event_cb, LV_EVENT_CLICKED, (void*)2);
    lv_obj_add_event_cb(btn_stats, button_event_cb, LV_EVENT_CLICKED, (void*)3);
    lv_obj_add_event_cb(btn_drink, button_event_cb, LV_EVENT_CLICKED, (void*)4);
}