#include <stdio.h>
#include "lvgl.h"
#include "drunkagotchi.h"

#define DECAY_INTERVAL_MS 10000 // Decay every 5 seconds
#define STAT_DECAY_AMOUNT 2    // Amount to decrease
#define BAC_DECAY_AMOUNT 0.01f // Amount to decrease BAC

static lv_timer_t * decay_timer;

void decrease_stats(lv_timer_t * timer) {
    // Decrease stats but ensure they don’t go below zero
    tama->happy = tama->happy > STAT_DECAY_AMOUNT ? tama->happy - STAT_DECAY_AMOUNT : 0;
    tama->full = tama->full > STAT_DECAY_AMOUNT ? tama->full - STAT_DECAY_AMOUNT : 0;
    tama->trained = tama->trained > STAT_DECAY_AMOUNT ? tama->trained - STAT_DECAY_AMOUNT : 0;
    tama->BAC = tama->BAC > BAC_DECAY_AMOUNT ? tama->BAC - BAC_DECAY_AMOUNT : 0;

    if (tama->state == 1)
    {
        homescreen_ui(disp_global); // Update the home screen UI
    }
    else if (tama->state == 2)
    {
        stats_ui(disp_global, tama); // Update the stats UI
    }

}

void start_stat_decay() {
    // Create a timer if it doesn’t already exist
    if (!decay_timer) {
        decay_timer = lv_timer_create(decrease_stats, DECAY_INTERVAL_MS, NULL);
    }
}

void stop_stat_decay() {
    // Stop the timer
    if (decay_timer) {
        lv_timer_del(decay_timer);
        decay_timer = NULL;
    }
}