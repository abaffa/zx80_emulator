#include "zx80_screen.h"
#include <assert.h>


static void zx80_screen_check_bounds(int x, int y)
{
    assert(x >= 0 && x < ZX80_WIDTH && y >= 0 && y < ZX80_HEIGHT);
}

void zx80_screen_set(struct zx80_screen* screen, int x, int y)
{
    zx80_screen_check_bounds(x, y);
    screen->pixels[y][x] = true;
}

void zx80_screen_clear(struct zx80_screen* screen)
{
    memset(screen->pixels, 0, sizeof(screen->pixels));
}

bool zx80_screen_is_set(struct zx80_screen* screen, int x, int y)
{
    zx80_screen_check_bounds(x, y);
    return screen->pixels[y][x];
}

bool zx80_screen_draw_sprite(struct zx80_screen* screen, int x, int y, const char* sprite, int num)
{
    bool pixel_collision = false;
    int lx, ly;
    for(ly = 0; ly < num; ly++){
        char c = sprite[ly];
        for(lx = 0; lx < 8; lx++)
        {
            if((c & (0b10000000 >> lx)) == 0)
                continue;

            if(screen->pixels[(ly+y) % ZX80_HEIGHT][(lx+x) % ZX80_WIDTH])
            {
                pixel_collision = true;
            }

            screen->pixels[(ly+y) % ZX80_HEIGHT][(lx+x) % ZX80_WIDTH] ^= true;
        }
    }
    return pixel_collision;
}