#include "lvgl.h"
#include "drunkagotchi.h"
#include <stdio.h>

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
                printf("Feed Healthy Food\n");
                // Call function to feed healthy
                break;
            case 1:
                printf("Feed Happy Food\n");
                // Call function to feed happy
                break;
            case 2:
                printf("Train\n");
                // Call function to train
                break;
            case 3:
                printf("View Stats\n");
                stats_ui(disp_global, tama);  // Update UI with stats
                break;
            case 4:
                printf("Drink\n");
                // Call function to drink
                break;
            case 5:
                printf("Back to HomeScreen\n");
                drunkagotchi_ui(disp_global);
                // Call function to drink
                break;
            default:
                break;
        }
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
    lv_obj_add_event_cb(btn_feed_healthy, event_handler, LV_EVENT_CLICKED, (void*)0);  // 0 for Feed Healthy
    lv_obj_add_event_cb(btn_feed_happy, event_handler, LV_EVENT_CLICKED, (void*)1);    // 1 for Feed Happy
    lv_obj_add_event_cb(btn_train, event_handler, LV_EVENT_CLICKED, (void*)2);         // 2 for Train
    lv_obj_add_event_cb(btn_stats, event_handler, LV_EVENT_CLICKED, (void*)3);         // 3 for Stats
    lv_obj_add_event_cb(btn_drink, event_handler, LV_EVENT_CLICKED, (void*)4);         // 4 for Drink

}