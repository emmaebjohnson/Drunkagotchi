// tamagotchi.h
#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H

typedef struct {
    int happy;
    int full;
    int trained;
    int drunk;
} Tamagotchi;

void feed_healthy(Tamagotchi *t);
void feed_happy(Tamagotchi *t);
void play_game(Tamagotchi *t);
void drink(Tamagotchi *t);

#endif
