// tamagotchi.h
#ifndef DRUNKAGOTCHI_H
#define DRUNKAGOTCHI_H

#include "lvgl.h"

typedef struct {
    int happy;
    int full;
    int trained;
    int drunk;
    float BAC;
} Tamagotchi;

extern Tamagotchi *tama;         // Global Tamagotchi object
extern lv_display_t *disp_global; // Global display object

void feed_healthy(Tamagotchi *t);
void feed_happy(Tamagotchi *t);
void play_game(Tamagotchi *t);
void drink(Tamagotchi *t);
void updateBAC(Tamagotchi *t);

void stats_ui(lv_display_t * disp, Tamagotchi * tama);
void event_handler(lv_event_t * e);
void homescreen_ui(lv_display_t * disp);
void minigame_ui(lv_display_t * disp);


#endif