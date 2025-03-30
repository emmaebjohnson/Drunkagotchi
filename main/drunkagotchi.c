// tamagotchi.c
#include "drunkagotchi.h"

void feed_healthy(Tamagotchi *t) {
    t->full += 10;
    t->happy += 2;
}

void feed_happy_food(Tamagotchi *t) {
    t->full += 2;
    t->happy += 10;
}

void play_game(Tamagotchi *t) {
    t->happy += 10;
    t->trained += 10;
}

