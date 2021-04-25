#ifndef ZX80SCREEN_H
#define ZX80SCREEN_H

#include <stdbool.h>
#include "config.h"
struct zx80_screen
{
    bool pixels[ZX80_HEIGHT][ZX80_WIDTH];
};

void zx80_screen_set(struct zx80_screen* screen, int x, int y);
void zx80_screen_clear(struct zx80_screen* screen);
bool zx80_screen_is_set(struct zx80_screen* screen, int x, int y);
bool zx80_screen_draw_sprite(struct zx80_screen* screen, int x, int y, const char* sprite, int num);
#endif