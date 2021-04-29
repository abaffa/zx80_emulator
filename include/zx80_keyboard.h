#ifndef ZX80KEYBOARD_H
#define ZX80KEYBOARD_H

#include <stdbool.h>
#include "config.h"
struct zx80_keyboard
{
    bool keyboard[ZX80_TOTAL_KEYS];
    const unsigned int* keyboard_map;
};

void zx80_keyboard_set_map(struct zx80_keyboard* keyboard, const unsigned int* map);
int zx80_keyboard_map(struct zx80_keyboard* keyboard, char key);
void zx80_keyboard_down(struct zx80_keyboard* keyboard, int key);
void zx80_keyboard_up(struct zx80_keyboard* keyboard, int key);
bool zx80_keyboard_is_down(struct zx80_keyboard* keyboard, int key);

#endif