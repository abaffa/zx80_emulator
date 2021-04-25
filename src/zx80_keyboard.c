#include "zx80_keyboard.h"
#include <assert.h>

static void zx80_keyboard_ensure_in_bounds(int key){
    assert(key >= 0 && key < ZX80_TOTAL_KEYS);
}

void zx80_keyboard_set_map(struct zx80_keyboard* keyboard, const char* map)
{
    keyboard->keyboard_map = map;
    int i;
    for(i = 0; i < ZX80_TOTAL_KEYS; i++)
        keyboard->keyboard[i] = false;
}

int zx80_keyboard_map(struct zx80_keyboard* keyboard, char key)
{
    
    int i;
    for(i = 0; i < ZX80_TOTAL_KEYS; i++)
    {
        if(keyboard->keyboard_map[i] == key)
        {
            return i;
        }
    }

    return -1;
}

void zx80_keyboard_down(struct zx80_keyboard* keyboard, int key)
{
    keyboard->keyboard[key] = true;
}

void zx80_keyboard_up(struct zx80_keyboard* keyboard, int key)
{
    keyboard->keyboard[key] = false; 
}

bool zx80_keyboard_is_down(struct zx80_keyboard* keyboard, int key)
{
    return keyboard->keyboard[key];
}