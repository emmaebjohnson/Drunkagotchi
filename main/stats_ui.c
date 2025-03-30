#include "lvgl.h"
#include "drunkagotchi.h"

// Global variables to store bar references
static lv_obj_t * bar_happy;
static lv_obj_t * bar_full;
static lv_obj_t * bar_trained;
static lv_obj_t * bar_drunk;
 
extern lv_display_t * disp_global;  // Global display variable
extern Tamagotchi * tama;  // Global Tamagotchi variable

static void update_bar(Tamagotchi* tama)
{
    lv_bar_set_value(bar_happy, tama->happy, LV_ANIM_ON);
    lv_bar_set_value(bar_full, tama->full, LV_ANIM_ON);
    lv_bar_set_value(bar_trained, tama->trained, LV_ANIM_ON);
    lv_bar_set_value(bar_drunk, tama->drunk, LV_ANIM_ON);
}

void stats_ui(lv_display_t * disp, Tamagotchi * tama)
{
    lv_obj_t * scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);
    //lv_disp_set_rotation(disp, LV_DISP_ROTATION_90);

    // Update if needed
    //update_bar(tama);

    // Main container (vertical layout)
    lv_obj_t * container = lv_obj_create(scr);
    lv_obj_set_size(container, 320, 240);
    lv_obj_center(container);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(container, 10, 0);

    lv_obj_t * status_label = lv_label_create(container);
    lv_label_set_text(status_label, "Your Tama's Stats :)");
    lv_obj_center(status_label);

    lv_obj_t * create_stat_bar(lv_obj_t * parent, const char * icon_text, int32_t initial_value) 
    {
        lv_obj_t * stat_container = lv_obj_create(parent);
        lv_obj_set_size(stat_container, 320, 30);
        lv_obj_set_flex_flow(stat_container, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_all(stat_container, 5, 0);

        // Icon
        lv_obj_t * icon = lv_label_create(stat_container);
        lv_label_set_text(icon, icon_text);
        lv_obj_set_style_text_font(icon, &lv_font_montserrat_14, 0);

        // Progress Bar
        static lv_style_t style_indic;
        lv_style_init(&style_indic);
        lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
        lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_PURPLE));
        lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);
        lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);

        lv_obj_t * bar = lv_bar_create(stat_container);
        lv_obj_set_size(bar, 250, 20);
        lv_bar_set_range(bar, 0, 100);
        lv_bar_set_value(bar, initial_value, LV_ANIM_OFF);
        lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);

        return bar;
    }

    // Create stat bars
    bar_happy = create_stat_bar(container, LV_SYMBOL_EYE_CLOSE, tama->happy);   // Happy
    bar_full = create_stat_bar(container, LV_SYMBOL_CUT, tama->full);    // Full
    bar_trained = create_stat_bar(container, LV_SYMBOL_PLAY, tama->trained);  // Trained
    bar_drunk = create_stat_bar(container, LV_SYMBOL_WARNING, tama->drunk); // Drunk

    // Button to go back to main menu
    lv_obj_t * back_btn = lv_btn_create(scr);  
    lv_obj_set_size(back_btn, 70, 30);
    lv_obj_t * label;
    lv_obj_add_event_cb(back_btn, event_handler, LV_EVENT_CLICKED, (void*)5);  // Back action
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_remove_flag(back_btn, LV_OBJ_FLAG_PRESS_LOCK);

    label = lv_label_create(back_btn);
    lv_label_set_text(label, "Back");
    lv_obj_center(label);
}


