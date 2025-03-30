// tamagotchi.h
#ifndef DRUNKAGOTCHI_H
#define DRUNKAGOTCHI_H

#include "lvgl.h"

typedef struct {
    int happy;
    int full;
    int trained;
    int drunk;
} Tamagotchi;

extern Tamagotchi *tama;         // Global Tamagotchi object
extern lv_display_t *disp_global; // Global display object

void feed_healthy(Tamagotchi *t);
void feed_happy(Tamagotchi *t);
void play_game(Tamagotchi *t);
void drink(Tamagotchi *t);

void stats_ui(lv_display_t * disp, Tamagotchi * tama);
void button_event_handler(lv_event_t * e);
void drunkagotchi_ui(lv_display_t * disp);


#endif