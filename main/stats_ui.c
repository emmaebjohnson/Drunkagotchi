#include "lvgl.h"

static void update_bar(void * bar, int32_t value)
{
    lv_bar_set_value((lv_obj_t *)bar, value, LV_ANIM_ON);
}

void stats_ui(lv_display_t * disp)
{
    lv_obj_t * scr = lv_display_get_screen_active(disp);
    lv_obj_clean(scr);
    lv_disp_set_rotation(disp, LV_DISP_ROTATION_90);

    // Main container (vertical layout)
    lv_obj_t * container = lv_obj_create(scr);
    lv_obj_set_size(container, 320, 240);
    lv_obj_center(container);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(container, 10, 0);

    lv_obj_t * status_label = lv_label_create(container);
    lv_label_set_text(status_label, "Your Tama's Stats :)");
    lv_obj_center(status_label);

    // Function to create a stat bar
    void create_stat_bar(lv_obj_t * parent, const char * icon_text, int32_t initial_value) {
        lv_obj_t * stat_container = lv_obj_create(parent);
        lv_obj_set_size(stat_container, 320, 40);
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
    }

    // Create stat bars
    create_stat_bar(container, LV_SYMBOL_EYE_CLOSE, 75);   // Happy
    create_stat_bar(container, LV_SYMBOL_CUT, 60);    // Full
    create_stat_bar(container, LV_SYMBOL_PLAY, 80);  // Trained
    create_stat_bar(container, LV_SYMBOL_WARNING, 30); // Drunk
}

